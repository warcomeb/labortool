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
// Session starting...
session_start();

require_once 'library/database.class.php';
require_once 'library/navigation.class.php';
require_once 'library/myutility.class.php';
require_once 'library/myerror.class.php';
require_once 'library/login.class.php';

// Specific print function for this project
require_once 'prjlibrary/projectpage.class.php';

// Config file
$config = parse_ini_file(__DIR__ . '/config/config.ini',true);

// Create database object
$db = Database::getInstance($config['database']);

// Save base url address
$baseUrl = $config['app']['urlbase'];

// Check if user is loggeg
list($status, $user) = Login::isLogged($db);

// When the user is logged, serve the request
if($status == MyError::_login_UserLogged)
{
    $nav = new Navigation();

    // Page object
    $page = new ProjectPage();

    if ($nav->isRoutable())
    {
        // Print header
        $page->printHeader($baseUrl,"");

        // Get current request
        $navLevel = $nav->getNavigationLevel();
        // Print sidebar and breadcrumbs
        $page->computeNavigationElements($navLevel);
        $page->printNavigation();
        $page->printBreadcrumbs();

        // Print requested page
        include($nav->getRoute());

        // Print footer
        $page->printFooter($config['app']['urlbase']);
    }
    else
    {
        $page->printHeader($config['app']['urlbase'],"Page Not Found");
        $page->printNavigation($config['app']['urlbase'],"");
        include('views/404.phtml');
        $page->printFooter($config['app']['urlbase']);
    }
}
else
{
    // Print login page
    include('views/login.phtml');
}