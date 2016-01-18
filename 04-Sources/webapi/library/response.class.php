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

require_once __DIR__ . '/../library/httpexception.class.php';

class Response
{
    protected $_format = 'json'; /* default */
    
    /**
     * Reply content of the request
     * @var mix
     */
//     protected $_result;
    
    /**
     * All data of the reply to client 
     * @var array
     */
    protected $_data = array(
            'request' => array(
                'controller' => '',
                'action'     => '',
                'id'         => '',
                'parameters' => array(),
            ),
            'result'  => array(
                'code'       => 0,
                'message'    => '',
                'contents'   => FALSE
            ),
    ); 
    
    protected $_isExist = FALSE;
    
    protected $_view;

    public function __construct(Request $request)
    {
        $this->_format = $request->getFormat();
        
        /* Standard reply if there aren't error! */
        $this->_data['result']['code'] = 200;
        $this->_data['result']['message'] = 'No Error!';

        $viewName = ucfirst($this->_format) . 'View';
        if (class_exists($viewName))
        {
            $this->_view = new $viewName();
            $this->_isExist = TRUE;
        }
        else
        {
            $this->_isExist = FALSE;
        }
    }
    
    public function setResult($result)
    {
        $this->_data['result']['contents'] = $result;
    }
    
    public function getResult()
    {
        $this->_data['result']['contents'];
    }
    
    public function setError($code, $message = '')
    {
        $this->_data['result']['code'] = $code;
        $this->_data['result']['message'] = $message;
    }

    public function dispatch()
    {    
        if (!$this->_isExist)
           throw new HTTPException("View doesn't exist!", HTTPEXCEPTION_INTERNALERROR);
    
        $this->_view->render($this->_data);
    }
    
    public function  isDispatchable()
    {
        return $this->_isExist;
    }
}
