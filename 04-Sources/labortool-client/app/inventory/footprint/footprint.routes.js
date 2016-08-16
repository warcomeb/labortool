"use strict";
var footprint_component_1 = require('./footprint.component');
var add_edit_component_1 = require('./add-edit/add-edit.component');
var view_component_1 = require('./view/view.component');
exports.footprintRoutes = [
    { path: 'inventory/footprint', component: footprint_component_1.FootprintComponent },
    { path: 'inventory/footprint/add', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/footprint/edit/:id', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/footprint/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=footprint.routes.js.map