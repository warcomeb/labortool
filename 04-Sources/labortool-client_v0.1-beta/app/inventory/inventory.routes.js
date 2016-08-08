"use strict";
var inventory_component_1 = require('./inventory.component');
var add_edit_component_1 = require('./add-edit/add-edit.component');
var view_component_1 = require('./view/view.component');
exports.inventoryRoutes = [
    { path: 'inventory', component: inventory_component_1.InventoryComponent },
    { path: 'inventory/add', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/edit/:id', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=inventory.routes.js.map