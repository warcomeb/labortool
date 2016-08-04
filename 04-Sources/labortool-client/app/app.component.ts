import {Component, Directive} from '@angular/core';
import {ROUTER_DIRECTIVES} from '@angular/router';
import {NavbarComponent} from './navbar/navbar.component';
import {HomeComponent} from './home/home.component';
import {ActivityComponent} from './activity/activity.component';
import {ProductionComponent} from './production/production.component';
import {ProjectComponent} from './project/project.component';
import {InventoryComponent} from './inventory/inventory.component';
import {AboutComponent} from './about/about.component';


@Component({
    selector: 'my-app',
    templateUrl: 'app/app.component.html',
    styleUrls: ['app/app.component.css'],
    directives: [ROUTER_DIRECTIVES, NavbarComponent, HomeComponent, ActivityComponent, ProductionComponent, ProjectComponent, InventoryComponent, AboutComponent],
    precompile: [HomeComponent, ActivityComponent, ProductionComponent, ProjectComponent, InventoryComponent, AboutComponent]
})

export class AppComponent {

}