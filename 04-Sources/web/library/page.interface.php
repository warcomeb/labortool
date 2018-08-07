<?php

interface Page
{
    public function printHeader($baseUrl, $pageTitle);
    public function printBreadcrumbs();
    public function printNavigation();
    public function printFooter($baseUrl);
}