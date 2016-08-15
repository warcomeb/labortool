"use strict";
var location_component_1 = require('./location.component');
var add_edit_component_1 = require('./add-edit/add-edit.component');
var view_component_1 = require('./view/view.component');
exports.locationRoutes = [
    { path: 'inventory/location', component: location_component_1.LocationComponent },
    { path: 'inventory/location/add', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/location/edit/:id', component: add_edit_component_1.AddEditComponent },
    { path: 'inventory/location/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=location.routes.js.map