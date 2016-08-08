"use strict";
var project_component_1 = require('./project.component');
var add_edit_component_1 = require('./add-edit/add-edit.component');
var view_component_1 = require('./view/view.component');
exports.projectRoutes = [
    { path: 'project', component: project_component_1.ProjectComponent },
    { path: 'project/edit/:id', component: add_edit_component_1.AddEditComponent },
    { path: 'project/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=project.routes.js.map