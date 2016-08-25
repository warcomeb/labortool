"use strict";
var location_component_1 = require('./location.component');
var add_component_1 = require('./add/add.component');
var edit_component_1 = require('./edit/edit.component');
var view_component_1 = require('./view/view.component');
exports.locationRoutes = [
    { path: 'inventory/location', component: location_component_1.LocationComponent },
    { path: 'inventory/location/add', component: add_component_1.AddComponent },
    { path: 'inventory/location/edit/:id', component: edit_component_1.EditComponent },
    { path: 'inventory/location/view/:id', component: view_component_1.ViewComponent }
];
//# sourceMappingURL=location.routes.js.map