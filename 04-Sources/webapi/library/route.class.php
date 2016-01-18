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

require_once __DIR__ . '/../library/httpexception.class.php';

class Route
{
    protected $_controller;
    protected $_action;
    protected $_command = array();

    protected $_isExist = false;

    public function __construct(Request $request)
    {
        $this->_command = $request->getCommand();
        
        $controllerName = ucfirst($this->_command['controller']) . 'Controller';
        if (class_exists($controllerName))
        {
            $this->_isExist = TRUE;
            $this->_controller = new $controllerName();
            $this->_action = $this->_command['action'] . 'Action';
        }
        else
        {
            $this->_isExist = FALSE;
        }
    }

    public function exec()
    {
        if (!$this->_isExist)
            throw new HTTPException("Request doesn't exist!", HTTPEXCEPTION_NOTFOUND);
        
        $actionName = $this->_action;
        $result = $this->_controller->$actionName($this->_command);
        
        if ($result !== FALSE)
        {
            return $result;
        }
        else
        {
            throw new HTTPException("Resource not found!", HTTPEXCEPTION_NOTFOUND);
        }
    }

    public function  routeExist()
    {
        return $this->_isExist;
    }
}
