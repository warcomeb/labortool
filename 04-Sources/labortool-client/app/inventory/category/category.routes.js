"use strict";
var category_component_1 = require('./category.component');
var add_edit_component_1 = require('./add-edit/add-edit.component');
var view_component_1 = require('./view/view.component');
exports.categoryRoutes = [
    { path: 'inventory/category', component: category_component_1.CategoryComponent },
    { path: 'inventory/category/add', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/category/edit/:id', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/category/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=category.routes.js.map