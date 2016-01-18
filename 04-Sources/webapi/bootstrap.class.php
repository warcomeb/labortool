<?php
/******************************************************************************
 * LabOrTool - WebAPI
 * Copyright (C) 2015-2016 Marco Giammarini
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
 ******************************************************************************/

//require_once __DIR__ . '/config/config.php';
 
class Bootstrap
{
/*    private $config = array ();

    public function __construct()
    {
        $this->config = parse_ini_file(__DIR__ . '/config/config.ini',true);
    }
*/    
    static public function getConfiguration()
    {
        return parse_ini_file(__DIR__ . '/config/config.ini',true);
    }
    
    static public function libraryLoad($classname)
    {
        if (preg_match('/[a-zA-Z]+Controller$/', $classname)) 
        {
            include __DIR__ . '/controllers/' . strtolower($classname) . '.class.php';
            return true;
        }
        elseif (preg_match('/[a-zA-Z]+Model$/', $classname))
        {
            include __DIR__ . '/models/' . strtolower($classname) . '.class.php';
            return true;
        } 
        elseif (preg_match('/[a-zA-Z]+View$/', $classname)) 
        {
            include __DIR__ . '/views/' . strtolower($classname) . '.class.php';
            return true;
        }
        elseif (preg_match('/[a-zA-Z]+Database$/', $classname)) 
        {
            include __DIR__ . '/database/' . strtolower($classname) . '.class.php';
            return true;
        }
    }
}
