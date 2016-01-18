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

class Request
{
    /**
     * URI components.
     */
    protected $uriElements;

    /**
     * The HTTP method this request was made in, either GET, POST, PUT or DELETE
     */
    protected $verb;

    protected $parameters;

    protected $command = array (
        'controller' => '',
        'action'     => '',
        'id'         => '',
        'parameters' => array(),
    );

    /**
     * The format of the request. Default is JSON.
     */
    protected $format = "json";

    public function __construct()
    {
        $this->verb = $_SERVER['REQUEST_METHOD'];
        $this->uriElements = explode('/', $_SERVER['PATH_INFO']);

        $this->parseParameters();        
        $this->parseCommand();
    }

    protected function parseParameters()
    {
        if (isset($_SERVER['QUERY_STRING']))
            parse_str($_SERVER['QUERY_STRING'], $parameters);

        $body = file_get_contents("php://input");
        
        $contenType = false;
        if (isset($_SERVER['CONTENT_TYPE']))
            $contentType = $_SERVER['CONTENT_TYPE'];

        switch ($contentType)
        {
        case 'application/json':
            $bodyParams = json_decode($body);
            if ($bodyParams) 
            {
                foreach ($bodyParams as $bodyParamName => $bodyParamValue) 
                {
                    $parameters[$bodyParamName] = $bodyParamValue;
                }
            }
            $this->format = 'json';
            break;
        case 'application/x-www-form-urlencoded':
            parse_str($body, $bodyParams);
            foreach ($bodyParams as $bodyParamName => $bodyParamValue)
            {
                $parameters[$bodyParamName] = $bodyParamValue;
            }
            $this->format = 'xml';
            break;
        default:
            // we could parse other supported formats here
            break;
        }
        $this->parameters = $parameters;
    }

    protected function parseCommand()
    {
        if (count($this->uriElements) && $this->uriElements === '')
            return;

        if (!empty($this->uriElements[1]))
            $this->command['controller'] = $this->uriElements[1];
    
        /* FIXME: Bisogna stare attenti: le richieste potrebbero essere anche delle ricerche! */
        if (!empty($this->uriElements[2]))
            $this->command['id'] = $this->uriElements[2];
        else
            $this->command['id'] = 0;

        switch ($this->verb)
        {
        case 'POST':
            $this->command['action'] = 'add';
            break;
        case 'GET':
            $this->command['action'] = 'get';
            break;
        case 'PUT':
            $this->command['action'] = 'update';
            break;
        case 'DELETE':
            $this->command['action'] = 'delete';
            break;
        default:
            /* TODO: ERRORE! */
            break;
        }

        if (!empty($this->parameters))
            $this->command['parameters'] = $this->parameters;
    }

    public function getFormat()
    {
        return $this->format;
    }

    public function getCommand()
    {
        return $this->command;
    }
}
