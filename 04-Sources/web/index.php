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
    $page->printHeader($config['app']['name'],$config['app']['version'],"");
    /* Print breadcrumbs */
    $breadcrumbs = $nav->getBreadcrumbs();
    $parameters = $nav->getParameters();
    $resourceId = $nav->getResourceId();
    
//     Page::printBreadcrumbs($site,$breadcrumbs);
//     include($nav->getRoute());
    $page->printFooter($config['app']['name'],$config['app']['version'],$config['app']['authors']);
}
else
{
    $page->printHeader($config['app']['name'],$config['app']['version'],"Page Not Found");
    echo "Page not found!";
    $page->printFooter($config['app']['name'],$config['app']['version'],$config['app']['authors']);
}