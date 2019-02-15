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
    $query =  "UPDATE " . PRJ_DB_TABLE_CUSTOMER_SUPPLIER . " SET
                Name='" . addslashes(stripslashes($_POST['name'])) . "',
             Address='" . addslashes(stripslashes($_POST['address'])) . "', 
                City='" . addslashes(stripslashes($_POST['city'])) . "', 
            District='" . addslashes(stripslashes($_POST['district'])) . "', 
             ZipCode='" . addslashes(stripslashes($_POST['zip'])) . "', 
             Country='" . addslashes(stripslashes($_POST['country'])) . "', 
               VATID='" . mb_strtoupper(addslashes(stripslashes($_POST['vat']))) . "',
                 NIN='" . mb_strtoupper(addslashes(stripslashes($_POST['nin']))) . "',
             Website='" . addslashes(stripslashes($_POST['website'])) ."',
               Email='" . addslashes(stripslashes($_POST['email'])) ."',
               Phone='" . addslashes(stripslashes($_POST['phone'])) . "', 
                 Fax='" . addslashes(stripslashes($_POST['fax'])) . "',
                IBAN='" . mb_strtoupper(addslashes(stripslashes($_POST['iban']))) . "', 
            Customer='" . addslashes(stripslashes($_POST['customer'])) . "',
            Supplier='" . addslashes(stripslashes($_POST['supplier'])) . "',
             Private='" . addslashes(stripslashes($_POST['private'])) . "',
                Note='" . addslashes(stripslashes($_POST['note'])) . "',
              Active='" . addslashes(stripslashes($_POST['active'])) . "' 
            WHERE Id={$_POST['id']}";

    // run query
    $data['query'] = $query;
    $affectedRows = $db->exec($query);
    if ($affectedRows === 1)
    {
        $data['status'] = 0;
        $data['id'] = $_POST['id'];
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
    $data['error'] = MyError::getErrorMessage($status);
}
echo json_encode($data);