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

require_once (realpath(dirname(__FILE__).'/../library/database.class.php'));
require_once (realpath(dirname(__FILE__).'/../library/usermanagement.class.php'));

// Add project define
require_once (realpath(dirname(__FILE__).'/../prjlibrary/prjdefine.php'));

// Config file
$config = parse_ini_file(realpath(dirname(__FILE__).'/../config/config.ini'),true);

// Array to save response
$data = array();
// Status Value:
// 0 - OK
// 1 - DATABASE ERROR
$data['status'] = 0;
$data['id'] = 0;
$data['error'] = "";

// Database object
$db = Database::getInstance($config['database']);

// Compose username
// The possible solutions is:
// 1 - name.surname
// 2 - name.surnameX where X is a progressive number
// Delete all space, and other chars
$username = UserManagement::composeUniqueUsername($db, PRJ_DB_TABLE_USER, $_POST['name'], $_POST['surname']);
if (empty($username))
{
    $data['status'] = 1;
    $data['error'] = "ERROR: Can't create unique username!";
    echo json_encode($data);
    return;
}

// Write the query
// FIXME: timestamp is usefull?
// FIXME: add profile image?
// FIXME: Log, is usefull?
$query = "INSERT INTO " . PRJ_DB_TABLE_USER . " 
          (Id, Code, Username, Password, Name, Surname, Email, Phone, Address, City, District, ZipCode, Country, NIN, Birthday, Note) 
          VALUES (NULL, 'U000000000',
          '{$username}',
          '{$_POST['password']}',
          '" . ucfirst(addslashes(stripslashes($_POST['name']))) . "',
          '" . ucfirst(addslashes(stripslashes($_POST['surname']))) . "',
          '" . addslashes(stripslashes($_POST['email'])) ."',
          '" . addslashes(stripslashes($_POST['phone'])) . "', 
          '" . addslashes(stripslashes($_POST['address'])) . "', 
          '" . addslashes(stripslashes($_POST['city'])) . "', 
          '" . addslashes(stripslashes($_POST['district'])) . "', 
          '" . addslashes(stripslashes($_POST['zip'])) . "', 
          '" . addslashes(stripslashes($_POST['country'])) . "', 
          '" . mb_strtoupper(addslashes(stripslashes($_POST['nin']))) . "',
          STR_TO_DATE('" . addslashes(stripslashes($_POST['birthday'])) . "','%d/%m/%Y'), 
          '" . addslashes(stripslashes($_POST['note'])) . "')";
$data['query'] = $query;
$affectedRows = $db->exec($query);
if ($affectedRows === 1)
{
    $data['id'] = $db->lastInsertId();
    $code = strval($data['id']);
    // Pad with zeros up to nine chars
    $code = str_pad($code, 9, "0", STR_PAD_LEFT);
    // Pad with U up to ten chars
    $code = str_pad($code, 10, "U", STR_PAD_LEFT);
    
    // Update code into database
    $query = "UPDATE User SET Code='{$code}' WHERE Id={$data['id']}"; 
    $affectedRows = $db->exec($query);
    if ($affectedRows === 1)
    {
        $data['status'] = 0;
    }
    else
    {
        $data['status'] = 1;
        $data['error'] = "ERROR: Can't create user code!";
    }
}
else
{
    $data['status'] = 1;
    $data['error'] = "ERROR: Can't add new user!";
}
echo json_encode($data);