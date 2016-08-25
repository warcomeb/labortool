"use strict";
var distributor_component_1 = require('./distributor.component');
var add_component_1 = require('./add/add.component');
var edit_component_1 = require('./edit/edit.component');
var view_component_1 = require('./view/view.component');
exports.distributorRoutes = [
    { path: 'inventory/distributor', component: distributor_component_1.DistributorComponent },
    { path: 'inventory/distributor/add', component: add_component_1.AddComponent },
    { path: 'inventory/distributor/edit/:id', component: edit_component_1.EditComponent },
    { path: 'inventory/distributor/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=distributor.routes.js.map