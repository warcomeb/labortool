"use strict";
var router_1 = require('@angular/router');
var about_routes_1 = require('./about/about.routes');
var activity_routes_1 = require('./activity/activity.routes');
var home_routes_1 = require('./home/home.routes');
var inventory_routes_1 = require('./inventory/inventory.routes');
var production_routes_1 = require('./production/production.routes');
var project_routes_1 = require('./project/project.routes');
var data_routes_1 = require('./data/data.routes');
var connection_route_1 = require('./connection/connection.route');
exports.routes = about_routes_1.aboutRoutes.concat(activity_routes_1.activityRoutes, home_routes_1.homeRoutes, inventory_routes_1.inventoryRoutes, production_routes_1.productionRoutes, project_routes_1.projectRoutes);
exports.appRouterProviders = [
    router_1.provideRouter(exports.routes),
    data_routes_1.dataProvider,
    connection_route_1.connectionProvider
];
//# sourceMappingURL=app.routes.js.map