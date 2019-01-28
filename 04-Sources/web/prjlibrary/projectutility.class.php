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

require_once 'prjdefine.php';

class ProjectUtility
{
    /**
     * This function compose an element code by union of start chars and 
     * element number. The output code is length fixed.
     * 
     * @param $id The number of the element.
     * @param $startCode An alfabetic string used to compose the code 
     *                   and identify the element.
     * @param $length The lenght of the output code, start char included.
     * @return Return the element code.
     */
    public static function getElementCode ($id, $startCode, $length)
    {
        // Convert code number into string
        $code = strval($id);
        $zeroPad = $length - strlen ($startCode);
        // Pad with zeros up start code chars
        $code = str_pad($code, $zeroPad, "0", STR_PAD_LEFT);
        // Add start code char
        return ($startCode . $code);
    }
}
