"use strict";
var unit_component_1 = require('./unit.component');
var view_component_1 = require('./view/view.component');
exports.unitRoutes = [
    { path: 'inventory/unit', component: unit_component_1.UnitComponent },
    { path: 'inventory/unit/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=unit.routes.js.map