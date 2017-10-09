<?php

interface Page
{
    public function printHeader($prjName, $prjVersion, $pageTitle);
    public function printBreadcrumbs($baseUrl, $elements);
    public function printMenu($baseUrl, $elements);
    public function printFooter($prjName, $prjVersion, $prjAuthor, $baseUrl);
}