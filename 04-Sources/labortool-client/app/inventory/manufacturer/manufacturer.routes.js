"use strict";
var manufacturer_component_1 = require('./manufacturer.component');
var add_edit_component_1 = require('./add-edit/add-edit.component');
var view_component_1 = require('./view/view.component');
exports.manufacturerRoutes = [
    { path: 'inventory/manufacturer', component: manufacturer_component_1.ManufacturerComponent },
    { path: 'inventory/manufacturer/add', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/manufacturer/edit/:id', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/manufacturer/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=manufacturer.routes.js.map