"use strict";
var production_component_1 = require('./production.component');
var add_edit_component_1 = require('./add-edit/add-edit.component');
var view_component_1 = require('./view/view.component');
exports.productionRoutes = [
    { path: 'production', component: production_component_1.ProductionComponent },
    { path: 'production/edit/:id', component: add_edit_component_1.AddEditComponent },
    { path: 'production/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=production.routes.js.map