<?php
/******************************************************************************
 * LabOrTool - WebAPI
 * Copyright (C) 2015-2016 Marco Giammarini
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
 ******************************************************************************/

require_once __DIR__ . '/../library/database.class.php';
require_once __DIR__ . '/../library/httpexception.class.php';
 
class DistributorDatabase 
{
    public function add(DistributorModel $distributor)
    {
        $db = Database::getInstance();

        $dbs = $db->prepare('INSERT INTO distributor ' .
                            '(DistributorName, DistributorWebsite) VALUES (:name, :website)');
        $dbs->bindValue(':name', $distributor->name, PDO::PARAM_STR);
        $dbs->bindValue(':website', $distributor->website, PDO::PARAM_STR);
        
        if ($dbs->execute())
            return $db->lastInsertId();
        else
            throw new HTTPException("Database Error", HTTPEXCEPTION_INTERNALERROR);
    }

    public function get($id)
    {
        $db = Database::getInstance();

        $query = 'SELECT * FROM distributor';
        if ($id !== 0)
            $query .=  ' WHERE DistributorId="' . $id .'"';
        
        $result = $db->query($query);
        if ($result)
        {
            $rows = $result->fetchAll(PDO::FETCH_ASSOC);

            if ($rows)
            {
                $i = 0;
                $resultArray = array();
                foreach ($rows as $row)
                {
                    $distributor = new DistributorModel($row['DistributorName'],
                                                        $row['DistributorId'],
                                                        $row['DistributorWebsite']);
                    $resultArray[$i] = $distributor->toArray();
                    $i++;
                }
                return $resultArray;
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            throw new HTTPException("Database Error", HTTPEXCEPTION_INTERNALERROR);
        }
    }

    public function update(DistributorModel $distributor)
    {
        $db = Database::getInstance();

        $dbs = $db->prepare('UPDATE distributor SET 
                             DistributorName = :name, 
                             DistributorWebsite = :website
                             WHERE DistributorId = :id');
        $dbs->bindValue(':name', $distributor->name, PDO::PARAM_STR);
        $dbs->bindValue(':website', $distributor->website, PDO::PARAM_STR);
        $dbs->bindValue(':id', $distributor->id, PDO::PARAM_INT);
        
        /* Control query execution! */
        if (!$dbs->execute())
            throw new HTTPException("Database Error", HTTPEXCEPTION_INTERNALERROR);

        if ($dbs->rowCount() !== 1)
            return FALSE;
        else
            return TRUE;
    }
    
    public function delete($id)
    {
        $db = Database::getInstance();
    
        $dbs = $db->prepare('DELETE FROM distributor WHERE DistributorId = :id');
        $dbs->bindParam(':id', $id, PDO::PARAM_INT);   

        /* Control query execution! */
        if (!$dbs->execute())
            throw new HTTPException("Database Error", HTTPEXCEPTION_INTERNALERROR);

        if ($dbs->rowCount() !== 1)
            return FALSE;
        else
            return TRUE;
    }
}