<?php 
/*
 * LabOrTool
 * Copyright (C) 2019 Marco Giammarini
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
// Start session
session_start();

require_once (realpath(dirname(__FILE__).'/../library/database.class.php'));
require_once (realpath(dirname(__FILE__).'/../library/usermanagement.class.php'));
require_once (realpath(dirname(__FILE__).'/../library/login.class.php'));

// Add project define
require_once (realpath(dirname(__FILE__).'/../prjlibrary/prjdefine.php'));
require_once (realpath(dirname(__FILE__).'/../prjlibrary/projectutility.class.php'));

// Config file
$config = parse_ini_file(realpath(dirname(__FILE__).'/../config/config.ini'),true);

// Array to save response
$data = array();
// Status Value:
// 0 - OK
// 1 - DATABASE ERROR
$data['status'] = 0;
$data['error'] = "";

// Database object
$db = Database::getInstance($config['database']);

// Check if user is logged
list($status, $user) = Login::isLogged($db);

// When the user is logged, add the customer/supplier
if ($status == MyError::_login_UserLogged)
{
    // Write the query
    // FIXME: timestamp is usefull?
    // FIXME: Log, is usefull?
    $query = "INSERT INTO " . PRJ_DB_TABLE_CUSTOMER_SUPPLIER . " 
            (Id, Code, Name, Active, Address, City, District, ZipCode, Country, VATID, NIN, Website, Email, Phone, Fax, IBAN, Customer, Supplier, Private, Note) 
            VALUES (NULL, 'C000000000',
            '" . addslashes(stripslashes($_POST['name'])) . "',
            '1',
            '" . addslashes(stripslashes($_POST['address'])) . "', 
            '" . addslashes(stripslashes($_POST['city'])) . "', 
            '" . addslashes(stripslashes($_POST['district'])) . "', 
            '" . addslashes(stripslashes($_POST['zip'])) . "', 
            '" . addslashes(stripslashes($_POST['country'])) . "', 
            '" . mb_strtoupper(addslashes(stripslashes($_POST['vat']))) . "',
            '" . mb_strtoupper(addslashes(stripslashes($_POST['nin']))) . "',
            '" . addslashes(stripslashes($_POST['website'])) ."',
            '" . addslashes(stripslashes($_POST['email'])) ."',
            '" . addslashes(stripslashes($_POST['phone'])) . "', 
            '" . addslashes(stripslashes($_POST['fax'])) . "',
            '" . mb_strtoupper(addslashes(stripslashes($_POST['iban']))) . "', 
            '" . addslashes(stripslashes($_POST['customer'])) . "',
            '" . addslashes(stripslashes($_POST['supplier'])) . "',
            '" . addslashes(stripslashes($_POST['private'])) . "',
            '" . addslashes(stripslashes($_POST['note'])) . "')";

    // run query
    $data['query'] = $query;
    $affectedRows = $db->exec($query);
    if ($affectedRows === 1)
    {
        $data['id'] = $db->lastInsertId();
        $code = ProjectUtility::getElementCode($data['id'],
                                               PRJ_CODE_CUSTOMER_SUPPLIER,
                                               PRJ_CODE_LENGTH);
        // Update code into database
        $query = "UPDATE " . PRJ_DB_TABLE_CUSTOMER_SUPPLIER . " SET Code='{$code}' WHERE Id={$data['id']}"; 
        $affectedRows = $db->exec($query);
        if ($affectedRows === 1)
        {
            $data['status'] = 0;
        }
        else
        {
            $data['status'] = 1;
            $data['error'] = MyError::getErrorMessage(MyError::_CustomerSupplier_ErrorCreateCode);
            // FIXME: remove the new element?
        }
    }
    else
    {
        $data['status'] = 1;
        $data['error'] = MyError::getErrorMessage(MyError::_CustomerSupplier_ErrorAddingNew);
    }
}
else
{
    $data['status'] = 1;
    $data['error'] = MyError::getErrorMessage($status);
}
echo json_encode($data);