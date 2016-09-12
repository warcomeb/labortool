"use strict";
var footprint_component_1 = require('./footprint.component');
var add_component_1 = require('./add/add.component');
var edit_component_1 = require('./edit/edit.component');
var view_component_1 = require('./view/view.component');
exports.footprintRoutes = [
    { path: 'inventory/footprint', component: footprint_component_1.FootprintComponent },
    { path: 'inventory/footprint/add', component: add_component_1.AddComponent },
    { path: 'inventory/footprint/edit/:id', component: edit_component_1.EditComponent },
    { path: 'inventory/footprint/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=footprint.routes.js.map