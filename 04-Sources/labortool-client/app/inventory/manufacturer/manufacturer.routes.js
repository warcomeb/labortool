"use strict";
var manufacturer_component_1 = require('./manufacturer.component');
var add_component_1 = require('./add/add.component');
var edit_component_1 = require('./edit/edit.component');
var view_component_1 = require('./view/view.component');
exports.manufacturerRoutes = [
    { path: 'inventory/manufacturer', component: manufacturer_component_1.ManufacturerComponent },
    { path: 'inventory/manufacturer/add', component: add_component_1.AddComponent },
    { path: 'inventory/manufacturer/edit/:id', component: edit_component_1.EditComponent },
    { path: 'inventory/manufacturer/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=manufacturer.routes.js.map