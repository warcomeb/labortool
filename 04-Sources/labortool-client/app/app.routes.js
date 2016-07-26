"use strict";
var router_1 = require('@angular/router');
var activity_component_1 = require('./activity/activity.component');
var home_component_1 = require('./home/home.component');
var production_component_1 = require('./production/production.component');
var project_component_1 = require('./project/project.component');
var inventory_component_1 = require('./inventory/inventory.component');
var about_component_1 = require('./about/about.component');
var add_activity_component_1 = require('./add/activity/add.activity.component');
var routes = [
    {
        path: '',
        component: home_component_1.HomeComponent
    },
    {
        path: 'activity',
        component: activity_component_1.ActivityComponent
    },
    {
        path: 'activity/add',
        component: add_activity_component_1.AddActivityComponent
    },
    {
        path: 'production',
        component: production_component_1.ProductionComponent
    },
    {
        path: 'project',
        component: project_component_1.ProjectComponent
    },
    {
        path: 'inventory',
        component: inventory_component_1.InventoryComponent
    },
    {
        path: 'about',
        component: about_component_1.AboutComponent
    }
];
exports.AppRouterProviders = [
    router_1.provideRouter(routes)
];
//# sourceMappingURL=app.routes.js.map