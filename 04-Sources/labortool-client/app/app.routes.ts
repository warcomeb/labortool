import {Component} from '@angular/core';
import {provideRouter, RouterConfig} from '@angular/router';
import {ActivityComponent} from './activity/activity.component';
import {HomeComponent} from './home/home.component';
import {ProductionComponent} from './production/production.component';
import {ProjectComponent} from './project/project.component';
import {InventoryComponent} from './inventory/inventory.component';
import {AboutComponent} from './about/about.component';
import {AddActiComponent} from './add/activity/add.component';
import {AddProdComponent} from './add/production/add.component';
import {AddProjComponent} from './add/project/add.component';
import {AddInveComponent} from './add/inventory/add.component';

const routes: RouterConfig = [
    {path: 'home', component: HomeComponent},
    {path: '', redirectTo: '/home', pathMatch: 'full'},
    {path: 'activity', component: ActivityComponent},
    {path: 'activity/add', component: AddActiComponent},
    {path: 'production', component: ProductionComponent},
    {path: 'production/add', component: AddProdComponent},
    {path: 'project', component: ProjectComponent},
    {path: 'project/add', component: AddProjComponent},
    {path: 'inventory', component: InventoryComponent},
    {path: 'inventory/add', component: AddInveComponent},
    {path: 'about', component: AboutComponent}
];

export const appRouterProviders = [
    provideRouter(routes)
]