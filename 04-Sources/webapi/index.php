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

require_once 'library/request.class.php';
require_once 'library/route.class.php';
require_once 'library/response.class.php';

require_once 'library/httpexception.class.php';

require_once 'bootstrap.class.php';
spl_autoload_register('Bootstrap::libraryLoad');

$result = NULL;

$request = new Request();
$route = new Route($request);

$response = new Response($request);

try 
{
    if ($route->routeExist())
        $result = $route->exec();
    else
        throw new HTTPException("Resource not found!", HTTPEXCEPTION_NOTFOUND);        

    $response->setResult($result);

}
catch (HTTPException $e)
{
    $response->setError($e->getCode(),$e->getMessage());
}

// Dispatch request
if ($response->isDispatchable())
    $response->dispatch();

/* END REQUEST */