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

require_once __DIR__ . '/../library/controller.interface.php';
require_once __DIR__ . '/../library/httpexception.class.php';

class ManufacturerController implements Controller
{
    function addAction($parameters)
    {
        $wrapper = new ManufacturerDatabase(); 
    
        if (!isset($parameters['parameters']['name']))
            throw new HTTPException("Manufacturer - Name Invalid", HTTPEXCEPTION_BADREQUEST);
        
        $manufacturer = new ManufacturerModel($parameters['parameters']['name']);
        $manufacturer->website = $parameters['parameters']['website'];
        
        /* Save!! */
        $result = $wrapper->add($manufacturer);
        return true;
    }

    function updateAction($parameters)
    {
        $wrapper = new ManufacturerDatabase();
    
        if (!isset($parameters['id']))
            throw new HTTPException("Manufacturer - Id Invalid", HTTPEXCEPTION_BADREQUEST);
        
        if (!isset($parameters['parameters']['name']) ||
            !isset($parameters['parameters']['website']))
            throw new HTTPException("Manufacturer - Parameters Invalid", HTTPEXCEPTION_BADREQUEST);
        
        $manufacturer = new ManufacturerModel($parameters['parameters']['name'],
                                              $parameters['id'],
                                              $parameters['parameters']['website']);

        /* Save operation!! */
        return $wrapper->update($manufacturer);
    }

    function deleteAction($parameters)
    {
        $wrapper = new ManufacturerDatabase(); 
    
        if (!isset($parameters['id']))
            throw new HTTPException("Manufacturer - Id Invalid", HTTPEXCEPTION_BADREQUEST);
        /* Save operation!! */
        return $wrapper->delete($parameters['id']);
   }

    function getAction($parameters)
    {
        $wrapper = new ManufacturerDatabase(); 

        if (isset($parameters['id']))
        {
            $id = $parameters['id'];
            return $wrapper->get($id);
        }
        else
        {
            throw new HTTPException("Manufacturer - Id Invalid", HTTPEXCEPTION_BADREQUEST);
        }
    }
}