<?php 
/*
 * LabOrTool
 * Copyright (C) 2018-2019 Marco Giammarini
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
// Start session
session_start();

require_once (realpath(dirname(__FILE__).'/../library/database.class.php'));
require_once (realpath(dirname(__FILE__).'/../library/myerror.class.php'));
require_once (realpath(dirname(__FILE__).'/../library/login.class.php'));

// Add project define
require_once (realpath(dirname(__FILE__).'/../prjlibrary/prjdefine.php'));

// Config file
$config = parse_ini_file(realpath(dirname(__FILE__).'/../config/config.ini'),true);

// Database object
$db = Database::getInstance($config['database']);

// Check if user is logged
list($status, $user) = Login::isLogged($db);

// When the user is not logged, try the login
if ($status == MyError::_login_UserNotLogged)
{
    // Check if username and password is empty
    // The only way to have an empty fields is external attack!
    if ((empty($_POST['username'])) || (empty($_POST['password'])))
    {
        echo json_encode(array(MyError::_login_EmptyData, 0, MyError::getErrorMessage(MyError::_login_EmptyData)));
    }
    else 
    {
        // Try log-in phase with ajax request data
        list($status, $user) = Login::doLogin($db, $_POST['username'], $_POST['password']);
        
        // Check the result
        if ($status == MyError::_login_UserLoggedIn)
        {
            echo json_encode(array($status, $user, MyError::getErrorMessage($status)));
        }
        else
        {
            echo json_encode(array($status, $user, MyError::getErrorMessage($status)));
        }
    }
}
else
{
    
}