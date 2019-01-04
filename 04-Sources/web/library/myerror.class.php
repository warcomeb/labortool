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

class MyError
{
    /**
     * 
     */
    const _login_UserLogged = 100;
    
    /**
     *
     */
    const _login_UserNotLogged = 101;
    
    /**
     *
     */
    const _login_NewUser = 102;
    
    /**
     * 
     */
    const _login_NoCoockie = 103;
    
    /**
     *
     */
    const _login_HackerTry = 104;
    
    /**
     *
     */
    const _login_SessionExpired = 105;
    
    /**
     *
     */
    const _login_DatabaseError = 106;
    
    /**
     *
     */
    const _login_DataError = 107;
    
    /**
     *
     */
    const _login_UserLoggedIn = 108;
    
    /**
     *
     */
    const _login_UserLoggedOut = 109;
    
    /**
     *
     */
    const _login_UserNotActive = 110;
    
    /**
     *
     */
    const _login_WrongPassword = 111;
    
    /**
     *
     */
    const _login_EmptyData = 112;
    
    /**
     * This function return a error message for each error code.
     *
     * @param int $code The error code
     * @return string A string with the relative error message.
     */
    public static function getErrorMessage($code)
    {
        switch ($code)
        {
        case self::_login_EmptyData:
            return "ERR[".self::_login_EmptyData."] Username e/o password vuoti.";
        default:
            return "ERR[0000] Errore non codificato!";
        }
    }
}