"use strict";
var manufacturer_routes_1 = require('./manufacturer/manufacturer.routes');
var distributor_routes_1 = require('./distributor/distributor.routes');
var location_routes_1 = require('./location/location.routes');
var footprint_routes_1 = require('./footprint/footprint.routes');
var category_routes_1 = require('./category/category.routes');
var cat_param_type_routes_1 = require('./cat-param-type/cat-param-type.routes');
var unit_routes_1 = require('./unit/unit.routes');
exports.inventoryRoutes = manufacturer_routes_1.manufacturerRoutes.concat(distributor_routes_1.distributorRoutes, location_routes_1.locationRoutes, footprint_routes_1.footprintRoutes, category_routes_1.categoryRoutes, cat_param_type_routes_1.catparamtypeRoutes, unit_routes_1.unitRoutes);
//# sourceMappingURL=inventory.routes.js.map