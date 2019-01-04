<?php
/*
 * LabOrTool
 * Copyright (C) 2018 Marco Giammarini
 *
 * Author(s):
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>
 */

require_once (realpath(dirname(__FILE__).'/../library/myerror.class.php'));

// Add project define
require_once (realpath(dirname(__FILE__).'/../prjlibrary/prjdefine.php'));

/**
 * Le funzioni contenute in questa permettono di gestire il login sicuro all'interno di un sistema senza ssl.
 * Per poter funzionare ha bisogno che l'utente abbia abilitato javascript ed i cookie e di un database. 
 *
 * Vengono riportate le tabelle che devono essere create nel database per gestire il login. 
 *
 * <code>
 * CREATE TABLE IF NOT EXISTS User (
 *   Id int(10) unsigned NOT NULL auto_increment,
 *   Username varchar(50) NOT NULL,
 *   Password varchar(50) NOT NULL,
 *   Nome varchar(50) NOT NULL,
 *   Active int(1) unsigned NOT NULL default '1',
 *   PRIMARY KEY  (Id)
 * ) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
 * 
 * CREATE TABLE IF NOT EXISTS UserSession (
 *   Id char(50) NOT NULL,
 *   UserId int(10) unsigned NOT NULL default '0',
 *   StartTime int(10) unsigned NOT NULL default '0',
 *   KEY uid (Id)
 * ) ENGINE=MyISAM DEFAULT CHARSET=utf8;
 * </code>
 *
 */
class Login
{
    /**
     * This function manage the logout operations
     *
     * @param Database  $db The database object
     * @return array L'array che viene restituito contiene nel primo campo il messaggio relativo a cosa è successo, e nel secondo NULL.
     */
    public static function doLogout ($db)
    {
        if (is_null(self::getSessionId()))
        {
            return array(MyError::_login_UserNotLogged, NULL);
        }
        else
        {
            // Delete into database the current session
            $query = "DELETE FROM ". PRJ_DB_TABLE_SESSION . " WHERE Id + ". $_SESSION['UserId'] ."'";
            $db->exec($query);
            
            // Destroy current session
            $_SESSION[] = array();
            session_destroy();
            // Open new session
            session_start();
            $_SESSION['UserAgent'] = md5($_SERVER['HTTP_USER_AGENT']);
            $_SESSION['RemoteAddress'] = md5($_SERVER['REMOTE_ADDR']);
            
            return array(MyError::_login_UserLoggedOut, NULL);
        }
    }
    
    /**
     * This function manage the login phase.
     *
     * @param mahsDB& $dbObj E' l'oggetto che permette la connessione al database, di qualunque tipo esso sia.
     * @param string $username The username entered by the user.
     * @param string $password The password entered by the user and managed by javascript.
     * @return array   An array with these information: on the first field a code with the result
     *                 in the second field NULL if no user logged, otherwise the user data.
     */
    public static function doLogin ($db, $username, $password)
    {
        if (isset($_SESSION['Key']))
        {
            $query = "SELECT * FROM " . PRJ_DB_TABLE_USER ." WHERE Username = '" . $username . "'";           
            $result = $db->query($query);
            if ($result)
            {
                // Only one row is possible...
                $rows = $result->fetchAll(PDO::FETCH_ASSOC);
                if (($rows) && (count($rows) == 1))
                {
                    // Check if user is active
                    if ($rows[0]['Active'] == 1)
                    {
                        // Crypto with SHA256 the password into the database concatenated with 
                        // a key randomly generated into the page
                        error_log("Form3-".$_SESSION['Key'] );
                        error_log("Form4-".$rows[0]['Password'].$_SESSION['Key'] );
                        $cript = hash('sha256', $rows[0]['Password'].$_SESSION['Key']);
                        error_log("Form5-".$cript );
                        error_log("Form5-".$password );
                        // Check if the previous result is the same abtained client side
                        if ($cript == $password)
                        {
                            $_SESSION['UserId'] = $rows[0]['Id'];
    
                            $userData = array(
                                'Name' => $rows[0]['Name'],
                                'Surname' => $rows[0]['Surname'],
                                'Id' => $rows[0]['Id'],
                                'Username' => $rows[0]['Username']);

                            // Delete into database other session of the same user
                            $query = "DELETE FROM ". PRJ_DB_TABLE_SESSION . " WHERE UserId='" .$rows[0]['Id'] . "'";
                            $db->exec($query);

                            // Save new session into database
                            $db->exec("INSERT INTO ". PRJ_DB_TABLE_SESSION . " (Id, UserId, StartTime)
                                          VALUES('".self::getSessionId()."', '".$rows[0]['Id']."', ".time().")");

                            return array(MyError::_login_UserLoggedIn, $userData);
                        }
                        else
                        {
                            // The password is wrong
                            return array(MyError::_login_WrongPassword, NULL);
                        }
                    }
                    else
                    {
                        // The user account is not active
                        return array(MyError::_login_UserNotActive, NULL);
                    }
                }
                else
                {
                    // The rows are greater than one... ERROR!
                    return array(MyError::_login_DataError, NULL);
                }
            }
            else
            {
                // Database error: no connetion? query wrong?...
                return array(MyError::_login_DatabaseError, NULL);
            }
        }
        else
        {
            // Problem with session and coockie
            return array(MyError::_login_NoCoockie, NULL);
        }
    }
    
    /**
     * This function check if user is logged into the system.
     * For this function is mondatory that the session was start with session_start at the begin of the page.
     *
     * @param Database $db           The database object
     * @return array   An array with these information: on the first field a code with the result
     *                 in the second field NULL if no user logged, otherwise the user data.
     */
    public static function isLogged ($db)
    {
        // Check if the user connecting for the first time
        if (isset($_SESSION['UserAgent']) && isset($_SESSION['RemoteAddress']))
        {
            // Check if user is connected
            if (!isset($_SESSION['UserId']))
                return array(MyError::_login_UserNotLogged, NULL);

            // Check if session variables is the same of the current user
            if (($_SESSION['UserAgent'] != md5($_SERVER['HTTP_USER_AGENT'])) &&
                ($_SESSION['RemoteAddress'] != md5($_SERVER['REMOTE_ADDR'])))
            {
                // The variables are different, so we destroy it!
                $_SESSION[] = array();
                session_destroy();
                // Open new session
                session_start();
                $_SESSION['UserAgent'] = md5($_SERVER['HTTP_USER_AGENT']);
                $_SESSION['RemoteAddress'] = md5($_SERVER['REMOTE_ADDR']);
                
                return array(MyError::_login_HackerTry, NULL);
            }
            else
            {
                // Check if coockies are active
                if (is_null(self::getSessionId()))
                {
                    // Destroy the current session
                    $_SESSION[] = array();
                    session_destroy();
                    // Open new connection
                    session_start();
                    $_SESSION['UserAgent'] = md5($_SERVER['HTTP_USER_AGENT']);
                    $_SESSION['RemoteAddress'] = md5($_SERVER['REMOTE_ADDR']);
                    
                    return array(MyError::_login_NoCoockie, NULL);
                }
                    
                // Check if the session was expired
                self::cleanExpiredSessions($db);
                $sessionId = self::getSessionId();
                
                // If session id is not present, return for session expired
                if(is_null($sessionId))
                {
                    return array(MyError::_login_SessionExpired, NULL);
                }
                
                $query = "SELECT U.Name as Name, U.Surname as Surname, U.Id as UserId, U.Username as Username
                          FROM ". PRJ_DB_TABLE_SESSION ." S,". PRJ_DB_TABLE_USER ." U
                          WHERE S.UserId = U.Id AND S.Id = '".$sessionId."'";
                
                $result = $db->query($query);
                if ($result)
                {
                    $rows = $result->fetchAll(PDO::FETCH_ASSOC);
                    if (($rows) && (count($rows) == 1))
                    {
                        $userData = array(
                            'Name' => $rows[0]['Name'],
                            'Surname' => $rows[0]['Surname'],
                            'Id' => $rows[0]['UserId'],
                            'Username' => $rows[0]['Username']);

                        return array(MyError::_login_UserLogged, $userData);
                    }
                    else 
                    {
                        // Destroy the current session
                        $_SESSION[] = array();
                        session_destroy();
                        // Open new connection
                        session_start();
                        $_SESSION['UserAgent'] = md5($_SERVER['HTTP_USER_AGENT']);
                        $_SESSION['RemoteAddress'] = md5($_SERVER['REMOTE_ADDR']);
                        
                        return array(MyError::_login_DatabaseError, NULL);
                    }
                }
                else
                {
                    // Destroy the current session
                    $_SESSION[] = array();
                    session_destroy();
                    // Open new connection
                    session_start();
                    $_SESSION['UserAgent'] = md5($_SERVER['HTTP_USER_AGENT']);
                    $_SESSION['RemoteAddress'] = md5($_SERVER['REMOTE_ADDR']);
                    
                    return array(MyError::_login_DatabaseError, NULL);
                }
            }
        }
        else
        {
            $_SESSION['UserAgent'] = md5($_SERVER['HTTP_USER_AGENT']);
            $_SESSION['RemoteAddress'] = md5($_SERVER['REMOTE_ADDR']);
            
            return array(MyError::_login_NewUser, NULL);
        }
    }
    
    /**
     * This function check if the current session is still valid and delete all expired sessions.
     *
     * @param Database $db The database object
     */
    public static function cleanExpiredSessions($db)
    {
        // Acquisisco la data di creazione della sessione relativo all'ID mostrato dall'utente.
        $query = "SELECT * FROM " . PRJ_DB_TABLE_SESSION . " WHERE Id='". self::getSessionID() . "'";
        $result = $db->query($query);
        if ($result)
        {
            $rows = $result->fetchAll(PDO::FETCH_ASSOC);
            foreach ($rows as $row)
            {
                if (($row['StartTime'] + LOGIN_EXPIRE_SESSION) <= time())
                {
                    // Destroy current session
                    $_SESSION[] = array();
                    session_destroy();
                    // Open new session
                    session_start();
                    $_SESSION['UserAgent'] = md5($_SERVER['HTTP_USER_AGENT']);
                    $_SESSION['RemoteAddress'] = md5($_SERVER['REMOTE_ADDR']);               
                }
            }
        }
        // Delete into database expired sessions
        $query = "DELETE FROM ". PRJ_DB_TABLE_SESSION . " WHERE StartTime + ". LOGIN_EXPIRE_SESSION ." <= ".time();
        $db->exec($query);
    }
    
    /**
     * This function return the current session id if coockies was enabled.
     *
     * @return string The current session id, NULL otherwise.
     */
    public static function getSessionId()
    {
        if (isset($_COOKIE['PHPSESSID']))
            return $_COOKIE['PHPSESSID'];
        else
            return NULL;
    }
    
    /**
     * This function generate a random key to use with password for login.
     */
    public static function addKey()
    {
        if (!isset($_SESSION['UserId']))
        {
            $_SESSION['Key'] =  hash('sha256',mt_rand());
            error_log($_SESSION['Key']);
//             $_SESSION['Key'] =  hash('sha256','Ciao');
        }
    }
}