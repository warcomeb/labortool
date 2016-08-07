import {Component, OnInit} from '@angular/core';
import {ROUTER_DIRECTIVES} from '@angular/router';
import {ProdClass} from '../classes/classes';
import {CallsService} from '../services/calls.service';
import {BreadcrumbsComponent} from '../breadcrumbs/breadcrumbs.component';
import {SearchProdComponent} from '../search/production/search.component';
import {AddProdBtnComponent} from '../button/production/add.button.component';
import {MemoryDataService} from '../services/memory.data.service';

@Component({
    selector: 'my-production',
    templateUrl: 'app/production/production.component.html',
    styleUrls: ['app/production/production.component.css'],
    directives: [ROUTER_DIRECTIVES, BreadcrumbsComponent, SearchProdComponent, AddProdBtnComponent]
})

export class ProductionComponent {
    
}