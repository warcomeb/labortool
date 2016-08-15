"use strict";
var distributor_component_1 = require('./distributor.component');
var add_edit_component_1 = require('./add-edit/add-edit.component');
var view_component_1 = require('./view/view.component');
exports.distributorRoutes = [
    { path: 'inventory/distributor', component: distributor_component_1.DistributorComponent },
    { path: 'inventory/distributor/add', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/distributor/edit/:id', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/distributor/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=distributor.routes.js.map