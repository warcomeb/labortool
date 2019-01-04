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

require_once (realpath(dirname(__FILE__).'/../library/myutility.class.php'));

/**
 *
 *
 */
class UserManagement
{
    public static function composeUniqueUsername ($db, $dbTable, $name, $surname)
    {
        // Convert accent chars
        $name = MyUtility::convertAccentCharacters($name);
        $surname = MyUtility::convertAccentCharacters($surname);

        // explode and lowercase name
        $nameParts = array_filter(preg_split("/[ ,.-]+/", strtolower($name)));
        // Take only the first part of the name
        $nameParts = array_slice($nameParts, 0, 1);
        // explode and lowercase surname
        $surnameParts = array_filter(preg_split("/[ ,.-]+/", strtolower($surname)));

        // Compose the username
        $username = ($nameParts[0] . ".");
        foreach ($surnameParts as $surnamePart)
        {
            $username .= $surnamePart;
        }

        // Check if is unique, otherwise add number
        $query = "SELECT * FROM " . $dbTable . " WHERE Username LIKE '%" . $username . "%'";
        $result = $db->query($query);
        if ($result)
        {
            $rows = $result->fetchAll(PDO::FETCH_ASSOC);
            if (($rows) && (count($rows) > 0))
            {
                $num = count ($rows);
                return $username . strval($num);
            }
            else 
            {
                return $username; 
            }
        }
        else 
        {
            return "";
        }
    }
}
