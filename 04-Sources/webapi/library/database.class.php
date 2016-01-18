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
 
class Database 
{
    private $_db;
    static $_instance;

    private function __construct() 
    {
        $config = Bootstrap::getConfiguration();
    
        $this->_db = new PDO('mysql:host=' . $config['database']['host'] . ';dbname=' . $config['database']['dbname'],
                        $config['database']['username'],
                        $config['database']['password']);
        $this->_db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    }

    private function __clone(){}

    public static function getInstance() 
    {
        if (!(self::$_instance instanceof self)) 
        {
            self::$_instance = new self();
        }
        return self::$_instance;
    }

    public function __call ($method, $args) 
    {
        if ( is_callable(array($this->_db, $method)) ) 
        {
            return call_user_func_array(array($this->_db, $method), $args);
        }
        else 
        {
            throw new Exception();
        }
    }
}