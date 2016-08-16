"use strict";
var manufacturer_routes_1 = require('./manufacturer/manufacturer.routes');
var distributor_routes_1 = require('./distributor/distributor.routes');
var location_routes_1 = require('./location/location.routes');
var footprint_routes_1 = require('./footprint/footprint.routes');
var category_routes_1 = require('./category/category.routes');
exports.inventoryRoutes = manufacturer_routes_1.manufacturerRoutes.concat(distributor_routes_1.distributorRoutes, location_routes_1.locationRoutes, footprint_routes_1.footprintRoutes, category_routes_1.categoryRoutes);
//# sourceMappingURL=inventory.routes.js.map