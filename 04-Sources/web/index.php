<?php

require_once 'library/database.class.php';
require_once 'library/navigation.class.php';

/* Specific print function for this project */
require_once 'prjlibrary/projectpage.class.php';

/* Config file */
$config = parse_ini_file(__DIR__ . '/config/config.ini',true);

//$db = Database::getInstance($config['database']);

$nav = new Navigation();
// Page object
$page = new ProjectPage();

if ($nav->isRoutable())
{
    $page->printHeader($config['app']['urlbase'],"");

// FIXME
//     $parameters = $nav->getParameters();
//     $resourceId = $nav->getResourceId();

    // Get current request
    $navLevel = $nav->getNavigationLevel();
    
    // Print sidebar and breadcrumbs
    $page->computeNavigationElements($navLevel);
    $page->printNavigation();
    $page->printBreadcrumbs();

    // Print request page
    include($nav->getRoute());
    $page->printFooter($config['app']['urlbase']);
}
else
{
    $page->printHeader($config['app']['urlbase'],"Page Not Found");
    $page->printNavigation($config['app']['urlbase'],"");
    include('views/404.phtml');
    $page->printFooter($config['app']['urlbase']);
}