"use strict";
var activity_component_1 = require('./activity.component');
var add_edit_component_1 = require('./add-edit/add-edit.component');
var view_component_1 = require('./view/view.component');
exports.activityRoutes = [
    { path: 'activity', component: activity_component_1.ActivityComponent },
    { path: 'activity/add', component: add_edit_component_1.AddEditComponent },
    { path: 'activity/edit/:id', component: add_edit_component_1.AddEditComponent },
    { path: 'activity/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=activity.routes.js.map