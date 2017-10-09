<?php

interface Page
{
    public function printHeader($baseUrl, $pageTitle);
    public function printBreadcrumbs($baseUrl, $elements);
    public function printMenu($baseUrl, $elements);
    public function printFooter($baseUrl);
}