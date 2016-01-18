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

require_once __DIR__ . '/../library/model.interface.php';

class DistributorModel implements Model
{
    private $_data = array();
    
    public function __construct($name, $id = 0, $website = 'http://')
    {
        $this->_data['name'] = $name;
        $this->_data['id'] = $id;
        $this->_data['website'] = $website;
    }

    public function __get($name)
    {
        if(!array_key_exists($name, $this->_data))
        {
            throw new Exception("Invalid property \"$name\"! ");
        }
        
        if(method_exists($this, 'get' . $name)) 
        {
            return call_user_func(array($this, 'get' . ucfirst($name)));
        } 
        else
        {
            return $this->_data[$name];
        }
    }
    
    public function __set($name, $value)
    {
        $this->_data[$name] = $value;
    }
    
    public function toArray()
    {
        $data = array(
            'id'      => $this->_data['id'],
            'name'    => $this->_data['name'],
            'website' => $this->_data['website']
        );
        
        return $data;
    }
}