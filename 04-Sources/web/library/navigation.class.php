<?php
/**
 *
 */

class Navigation
{
    protected $_action = array ('add', 'view', 'delete', 'list', 'update');

    protected $_uriElements;

    protected $_request = array (
        'module'     => '',
        'controller' => '',
        'action'     => '',
        'id'         => '',
        'parameters' => array(),
    );

    /** Addess of view file */
    protected $_address;
    
    /** String that contain current navigation level */
    protected $_navLevel;

    public function __construct()
    {
        $this->_uriElements = explode('/', $_SERVER['PATH_INFO']);

        $this->_parse();
        $this->_route();
    }

    protected function _parse()
    {
        /* Default page */
        if (count($this->_uriElements) && $this->_uriElements === '')
        {
            $this->_request['module'] = 'home';
            $this->_request['controller'] = 'home';
            return;
        }

        /* Select module */
        if (!empty($this->_uriElements[1]))
        {
            $this->_request['module'] = $this->_uriElements[1];
        }
        else
        {
            $this->_request['module'] = 'home';
            $this->_request['controller'] = 'home';
            return;
        }
        
        /* Select controller */
        if (!empty($this->_uriElements[2]))
        {
            $this->_request['controller'] = $this->_uriElements[2];
        }
        else
        {
            $this->_request['controller'] = 'home';
            return;
        }

        /* Select action */
        if (!empty($this->_uriElements[3]))
        {
            $this->_request['action'] = $this->_uriElements[3];
        }
        else
        {
            $this->_request['action'] = 'list';
            return;
        }

        /* FIXME: Bisogna stare attenti: le richieste potrebbero essere anche delle ricerche! */
        if (!empty($this->_uriElements[4]))
            $this->_request['id'] = $this->_uriElements[4];
        else
            $this->_request['id'] = 0;

        /*if (!empty($this->parameters))
            $this->_request['parameters'] = $this->parameters;*/
    }

    protected function _route()
    {
        $address = __DIR__ . '/../views/';

        if (!empty($this->_request['module']))
        {
            $address .= $this->_request['module'];
            $this->_navLevel = $this->_request['module'];
        }
        
        if (!empty($this->_request['controller']))
        {
            $address .= '/' . $this->_request['controller'];
            $this->_navLevel .= '_' . $this->_request['controller'];
        }

        if (!empty($this->_request['action']))
        {
            $address .= '/' . $this->_request['action'];
            $this->_navLevel .= '_' . $this->_request['action'];
        }

        $this->_address = $address . '.phtml';
    }

    public function isRoutable()
    {
        return file_exists($this->_address);
    }

    public function getRoute()
    {
        return $this->_address;
    }
    
    public function getNavigationLevel()
    {
        return $this->_navLevel;
    }

    public function getParameters()
    {
        return $this->_request['parameters'];
    }

    public function getResourceId()
    {
        return $this->_request['id'];
    }

};
