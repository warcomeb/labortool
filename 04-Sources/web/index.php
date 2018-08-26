<?php

require_once 'library/database.class.php';
require_once 'library/navigation.class.php';
require_once 'library/myutility.class.php';

/* Specific print function for this project */
require_once 'prjlibrary/projectpage.class.php';

/* Config file */
$config = parse_ini_file(__DIR__ . '/config/config.ini',true);

// Database object
$db = Database::getInstance($config['database']);

// Save base url address
$baseUrl = $config['app']['urlbase'];

$nav = new Navigation();
// Page object
$page = new ProjectPage();

if ($nav->isRoutable())
{
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