"use strict";
var cat_param_type_component_1 = require('./cat-param-type.component');
var view_component_1 = require('./view/view.component');
exports.categoryRoutes = [
    { path: 'inventory/category', component: cat_param_type_component_1.CatParamTypeComponent },
    { path: 'inventory/category/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=cat-param-type.routes.js.map