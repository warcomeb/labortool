<?php

require_once 'library/page.interface.php';
require_once 'prjdefine.php';

class ProjectPage implements Page
{
    protected $_baseUrl;

    protected $_breadcrumbs = array ();

    protected $_sidebar = array
    (
        array (
            'name'   => 'Dashboard',
            'id'     => 'home',
            'url'    => 'home',
            'title'  => 'Dashboard dell\'utente',
            'active' => FALSE,
            'logo'   => 'fas fa-tachometer-alt',
            'sub'    => array(),
        ),

        array (
            'name'   => 'Anagrafica',
            'id'     => 'records',
            'url'    => 'records',
            'title'  => 'Gestione anagrafiche',
            'active' => FALSE,
            'logo'   => 'fas fa-microchip',
            'sub'    => array(
                array (
                    'name'   => 'Articoli',
                    'id'     => 'article',
                    'url'    => 'records/article',
                    'title'  => 'Anagrafica Articoli',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Clienti/Fornitori',
                    'id'     => 'customer-supplier',
                    'url'    => 'records/customer-supplier',
                    'title'  => 'Anagrafica Clienti e Fornitori',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Produttori',
                    'id'     => 'manufacturer',
                    'url'    => 'records/manufacturer',
                    'title'  => 'Anagrafica Produttori',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Collaboratori',
                    'id'     => 'employee',
                    'url'    => 'records/employee',
                    'title'  => 'Anagrafica Collaboratori',
                    'active' => FALSE,
                ),
            ),
        ),

        array (
            'name'   => 'Gestione',
            'id'     => 'management',
            'url'    => 'management',
            'title'  => 'Gestione e Pianificazione',
            'active' => FALSE,
            'logo'   => 'far fa-calendar-alt',
            'sub'    => array(
                array (
                    'name'   => 'Progetti',
                    'id'     => 'project',
                    'url'    => 'management/project',
                    'title'  => 'Gestione Progetti',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Schede Elettroniche',
                    'id'     => 'board',
                    'url'    => 'management/board',
                    'title'  => 'Gestione Schede Elettroniche',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Attività',
                    'id'     => 'activity',
                    'url'    => 'management/activity',
                    'title'  => 'Gestione Attività',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Produzioni',
                    'id'     => 'production',
                    'url'    => 'management/production',
                    'title'  => 'Gestione Produzioni',
                    'active' => FALSE,
                ),
            ),
        ),

        array (
            'name'   => 'Magazzino',
            'id'     => 'warehouse',
            'url'    => 'warehouse',
            'title'  => 'Gestione magazzino',
            'active' => FALSE,
            'logo'   => 'fas fa-warehouse',
            'sub'    => array(
                array (
                    'name'   => 'Status',
                    'id'     => 'status',
                    'url'    => 'warehouse/status',
                    'title'  => 'Stato Magazzino',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Carico/Scarico',
                    'id'     => 'movements',
                    'url'    => 'warehouse/movements',
                    'title'  => 'Gestione Carico/Scarico',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Inventario',
                    'id'     => 'inventory',
                    'url'    => 'warehouse/inventory',
                    'title'  => 'Gestione Inventario',
                    'active' => FALSE,
                ),

            ),
        ),

        array (
            'name'   => 'Vendite',
            'id'     => 'sales',
            'url'    => 'sales',
            'title'  => 'Gestione vendite',
            'active' => FALSE,
            'logo'   => 'far fa-money-bill-alt',
            'sub'    => array(
                array (
                    'name'   => 'Offerte',
                    'id'     => 'offer',
                    'url'    => 'sales/offer',
                    'title'  => 'Gestione Offerte',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Ordini',
                    'id'     => 'order',
                    'url'    => 'sales/order',
                    'title'  => 'Gestione Ordini di Vendita',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'DDT',
                    'id'     => 'transport-document',
                    'url'    => 'sales/transport-document',
                    'title'  => 'Gestione DDT di Vendita',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Fatture',
                    'id'     => 'invoice',
                    'url'    => 'sales/invoice',
                    'title'  => 'Gestione Fatture di Vendita',
                    'active' => FALSE,
                ),
            ),
        ),

        array (
            'name'   => 'Acquisti',
            'id'     => 'purchases',
            'url'    => 'purchases',
            'title'  => 'Gestione Acquisti',
            'active' => FALSE,
            'logo'   => 'fas fa-cart-arrow-down',
            'sub'    => array(
                array (
                    'name'   => 'Ordini',
                    'id'     => 'order',
                    'url'    => 'purchases/order',
                    'title'  => 'Gestione Ordini di Acquisto',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'DDT',
                    'id'     => 'transport-document',
                    'url'    => 'purchases/transport-document',
                    'title'  => 'Gestione DDT di Acquisto',
                    'active' => FALSE,
                ),
                array (
                    'name'   => 'Fatture',
                    'id'     => 'invoice',
                    'url'    => 'purchases/invoice',
                    'title'  => 'Gestione Fatture di Acquisto',
                    'active' => FALSE,
                ),
            ),
        ),

        array (
            'name'   => 'Report',
            'id'     => 'report',
            'url'    => 'report',
            'title'  => 'Report dell\'utente',
            'active' => FALSE,
            'logo'   => 'fas fa-chart-line',
            'sub'    => array(),
        ),

        array (
            'name'   => 'About',
            'id'     => 'about',
            'url'    => 'about',
            'title'  => 'Informazioni su LabOrTool',
            'active' => FALSE,
            'logo'   => 'far fa-question-circle',
            'sub'    => array(),
        ),
    );

    public function __construct($baseUrl) 
    {
        $this->_baseUrl = $baseUrl;
    }

    public function printHeader($pageTitle)
    {
        $baseUrl = $this->_baseUrl;
        include('views/header.phtml');
    }

    public function printBreadcrumbs()
    {
        $baseUrl = $this->_baseUrl;
        include('views/breadcrumbs.phtml');
    }

    public function printNavigation()
    {
        $baseUrl = $this->_baseUrl;
        include('views/navbar.phtml');
    }

    public function printFooter()
    {
        $baseUrl = $this->_baseUrl;
        include('views/footer.phtml');
    }

    public function computeNavigationElements($navLevel)
    {
        // Check breadcrumbs and sidebar
        // Parse the current navigation level
        $levels = explode('_',$navLevel);

        if ($levels[0] === 'home')
        {
            // Save only the name
            $this->_breadcrumbs[0] = array (
                'name'  => $this->_sidebar[0]['name'],
            );
            // Put this menu level to ACTIVE!
            $this->_sidebar[0]['active'] = TRUE;
        }
        else 
        {
            // Save all the data
            $this->_breadcrumbs[0] = array (
                'name'  => $this->_sidebar[0]['name'],
                'url'   => $this->_sidebar[0]['url'],
                'title' => $this->_sidebar[0]['title'],
            ); 
            
            // Starting from the second member of menu
            $level = 0;
            for ($i = 1; $i < count($this->_sidebar); $i++)
            {
                if ($this->_sidebar[$i]['id'] === $levels[0])
                {
                    $this->_breadcrumbs[1] = array (
                        'name'  => $this->_sidebar[$i]['name'],
                        'url'   => $this->_sidebar[$i]['url'],
                        'title' => $this->_sidebar[$i]['title'],
                    );
                    // Save current module level
                    $level = $i;
                    
                    // Put this menu level to ACTIVE!
                    $this->_sidebar[$i]['active'] = TRUE;
                    break;
                }
            }
            
            if (count($levels) > 1)
            {
                for ($i = 1; $i < count($this->_sidebar[$level]['sub']); $i++)
                {
                    if ($this->_sidebar[$level]['sub'][$i]['id'] === $levels[1])
                    {
                        $this->_breadcrumbs[1]['name'] .= " " . $this->_sidebar[$level]['sub'][$i]['name'];
                        $this->_breadcrumbs[1]['url'] = $this->_sidebar[$level]['sub'][$i]['url'];
                        $this->_breadcrumbs[1]['title'] = $this->_sidebar[$level]['sub'][$i]['title'];
                        // Save current module level
                        $level = $i;
                        break;
                    }
                }
            }
            
            // if action is present, add to the breadcrumbs
            if (count($levels) > 2)
            {
                $text = '';
                if ('add' === $levels[2])
                {
                    $text = 'Inserimento';
                }
                else if ('view' === $levels[2])
                {
                    $text = 'Visualizza';
                }
                else if ('edit' === $levels[2])
                {
                    $text = 'Modifica';
                }
                
                if (!empty($text))
                {
                    $this->_breadcrumbs[2] = array (
                        'name'  => $text,
                    );
                }
            }
        }
    }
}
