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

class DistributorController implements Controller
{
    function addAction($parameters)
    {
        $wrapper = new DistributorDatabase(); 
    
        if (!isset($parameters['parameters']['name']))
            throw new HTTPException("Distributor - Name Invalid", HTTPEXCEPTION_BADREQUEST);
        
        $distributor = new DistributorModel($parameters['parameters']['name']);
        $distributor->website = $parameters['parameters']['website'];
        
        /* Save!! */
        $result = $wrapper->add($distributor);
        return true;
    }

    function updateAction($parameters)
    {
        $wrapper = new DistributorDatabase();
    
        if (!isset($parameters['id']))
            throw new HTTPException("Distributor - Id Invalid", HTTPEXCEPTION_BADREQUEST);
        
        if (!isset($parameters['parameters']['name']) ||
            !isset($parameters['parameters']['website']))
            throw new HTTPException("Distributor - Parameters Invalid", HTTPEXCEPTION_BADREQUEST);
        
        $distributor = new DistributorModel($parameters['parameters']['name'],
                                            $parameters['id'],
                                            $parameters['parameters']['website']);

        /* Save operation!! */
        return $wrapper->update($distributor);
    }

    function deleteAction($parameters)
    {
        $wrapper = new DistributorDatabase(); 
    
        if (!isset($parameters['id']))
            throw new HTTPException("Distributor - Id Invalid", HTTPEXCEPTION_BADREQUEST);
        /* Save operation!! */
        return $wrapper->delete($parameters['id']);
   }

    function getAction($parameters)
    {
        $wrapper = new DistributorDatabase(); 

        if (isset($parameters['id']))
        {
            $id = $parameters['id'];
            return $wrapper->get($id);
        }
        else
        {
            throw new HTTPException("Distributor - Id Invalid", HTTPEXCEPTION_BADREQUEST);
        }
    }
}