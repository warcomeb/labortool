import {Component, OnInit} from '@angular/core';
import {ROUTER_DIRECTIVES} from '@angular/router';
import {ProjClass} from '../classes/classes';
import {CallsService} from '../services/calls.service';
import {BreadcrumbsComponent} from '../breadcrumbs/breadcrumbs.component';
import {SearchProjComponent} from '../search/project/search.component';
import {AddProjBtnComponent} from '../button/project/add.button.component';
import {MemoryDataService} from '../services/memory.data.service';

@Component({
    selector: 'component-project',
    templateUrl: 'app/project/project.component.html',
    styleUrls: ['app/project/project.component.css'],
    directives: [ROUTER_DIRECTIVES, BreadcrumbsComponent, SearchProjComponent, AddProjBtnComponent]
})

export class ProjectComponent {
    
}