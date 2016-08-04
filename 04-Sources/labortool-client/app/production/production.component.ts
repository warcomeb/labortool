import {Component, OnInit} from '@angular/core';
import {ROUTER_DIRECTIVES} from '@angular/router';
import {ProductionClass} from '../classes/classes';
import {CallsService} from '../services/calls.service';
import {BreadcrumbsComponent} from '../breadcrumbs/breadcrumbs.component';
import {SearchProductionComponent} from '../search/production/search.production.component';
import {AddBtnProdComponent} from '../button/production/add.button.component';
import {Fake_DataService} from '../fake_data/fake_data.service';

@Component({
    selector: 'my-production',
    templateUrl: 'app/production/production.component.html',
    styleUrls: ['app/production/production.component.css'],
    directives: [ROUTER_DIRECTIVES, BreadcrumbsComponent, SearchProductionComponent, AddBtnProdComponent]
})

export class ProductionComponent {
    
}