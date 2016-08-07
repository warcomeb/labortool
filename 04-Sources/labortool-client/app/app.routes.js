"use strict";
var router_1 = require('@angular/router');
var activity_component_1 = require('./activity/activity.component');
var home_component_1 = require('./home/home.component');
var production_component_1 = require('./production/production.component');
var project_component_1 = require('./project/project.component');
var inventory_component_1 = require('./inventory/inventory.component');
var about_component_1 = require('./about/about.component');
var add_component_1 = require('./add/activity/add.component');
var add_component_2 = require('./add/production/add.component');
var add_component_3 = require('./add/project/add.component');
var add_component_4 = require('./add/inventory/add.component');
var routes = [
    { path: 'home', component: home_component_1.HomeComponent },
    { path: '', redirectTo: '/home', pathMatch: 'full' },
    { path: 'activity', component: activity_component_1.ActivityComponent },
    { path: 'activity/add', component: add_component_1.AddActiComponent },
    { path: 'production', component: production_component_1.ProductionComponent },
    { path: 'production/add', component: add_component_2.AddProdComponent },
    { path: 'project', component: project_component_1.ProjectComponent },
    { path: 'project/add', component: add_component_3.AddProjComponent },
    { path: 'inventory', component: inventory_component_1.InventoryComponent },
    { path: 'inventory/add', component: add_component_4.AddInveComponent },
    { path: 'about', component: about_component_1.AboutComponent }
];
exports.appRouterProviders = [
    router_1.provideRouter(routes)
];
//# sourceMappingURL=app.routes.js.map