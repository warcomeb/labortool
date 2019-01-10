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

class Navigation
{
    protected $_action = array ('add', 'view', 'delete', 'list', 'update');

    protected $_uriElements;

    protected $_request = array (
        'module'     => '',
        'controller' => '',
        'action'     => '',
        'id'         => '',
        'parameters' => array(),
    );

    /** Addess of view file */
    protected $_address;
    
    /** String that contain current navigation level */
    protected $_navLevel;

    public function __construct()
    {
        $this->_uriElements = explode('/', $_SERVER['REQUEST_URI']);

        $this->_parse();
        $this->_route();
    }

    protected function _parse()
    {
        /* Default page */
        if (count($this->_uriElements) && $this->_uriElements === '')
        {
            $this->_request['module'] = 'home';
            $this->_request['controller'] = 'home';
            return;
        }

        /* Select module */
        if (!empty($this->_uriElements[1]))
        {
            $this->_request['module'] = $this->_uriElements[1];
        }
        else
        {
            $this->_request['module'] = 'home';
            $this->_request['controller'] = 'home';
            return;
        }
        
        /* Select controller */
        if (!empty($this->_uriElements[2]))
        {
            $this->_request['controller'] = $this->_uriElements[2];
        }
        else
        {
            $this->_request['controller'] = 'home';
            return;
        }

        /* Select action */
        if (!empty($this->_uriElements[3]))
        {
            $this->_request['action'] = $this->_uriElements[3];
        }
        else
        {
            if (strcmp($this->_request['controller'],'home') !== 0)
                $this->_request['action'] = 'list';
            return;
        }

        /* FIXME: Bisogna stare attenti: le richieste potrebbero essere anche delle ricerche! */
        if (!empty($this->_uriElements[4]))
            $this->_request['id'] = $this->_uriElements[4];
        else
            $this->_request['id'] = 0;

        /*if (!empty($this->parameters))
            $this->_request['parameters'] = $this->parameters;*/
    }

    protected function _route()
    {
        $address = __DIR__ . '/../views/';

        if (!empty($this->_request['module']))
        {
            $address .= $this->_request['module'];
            $this->_navLevel = $this->_request['module'];
        }
        
        if (!empty($this->_request['controller']))
        {
            $address .= '/' . $this->_request['controller'];
            $this->_navLevel .= '_' . $this->_request['controller'];
        }

        if (!empty($this->_request['action']))
        {
            $address .= '/' . $this->_request['action'];
            $this->_navLevel .= '_' . $this->_request['action'];
        }

        $this->_address = $address . '.phtml';
    }

    public function isRoutable()
    {
        return file_exists($this->_address);
    }

    public function getRoute()
    {
        return $this->_address;
    }
    
    public function getNavigationLevel()
    {
        return $this->_navLevel;
    }

    public function getParameters()
    {
        return $this->_request['parameters'];
    }

    public function getResourceId()
    {
        if (!empty($this->_request['id']) && is_numeric($this->_request['id'])) 
            return $this->_request['id'];
        else 
            return 0;
    }

};
