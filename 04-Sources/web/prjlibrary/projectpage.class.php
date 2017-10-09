<?php

require_once 'library/page.interface.php';
require_once 'prjdefine.php';

class ProjectPage implements Page
{
    public function printHeader($baseUrl, $pageTitle)
    {
        include('views/header.phtml');
    }
    
    public function printBreadcrumbs($baseUrl, $elements)
    {
        
    }
    
    public function printMenu($baseUrl, $elements)
    {
        
    }
    
    public function printFooter($baseUrl)
    {
        include('views/footer.phtml');
    }
    
//     static public function printBreadcrumbs($baseUrl,$elements)
//     {
//         echo "<ol class=\"breadcrumb\">\n";
//         if (count($elements) == 0)
//         {
//             echo "\t<li class=\"active\">Home</li>\n";
//         }
//         else
//         {
//             echo "\t<li><a href=\"{$baseUrl}\">Home</a></li>\n";

//             $i = 0;
//             $url = $baseUrl;
//             foreach ($elements as $e)
//             {
//                 $url .= "/" . $e;
//                 if ($i == (count($elements)-1))
//                     echo "\t<li class=\"active\">".ucfirst($e)."</li>\n";
//                 else
//                     echo "\t<li><a href=\"{$url}\">".ucfirst($e)."</a></li>\n";

//                 $i++;
//             }
//         }
//         echo "</ol>\n";
//     }

//     static public function printAction()
//     {

//     }
}
