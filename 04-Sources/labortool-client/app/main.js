"use strict";
var platform_browser_dynamic_1 = require('@angular/platform-browser-dynamic');
var http_1 = require('@angular/http');
var host_component_1 = require('./configs/host.component');
var app_component_1 = require('./app.component');
var app_routes_1 = require('./app.routes');
var fake_data_service_1 = require('./fake_data/fake_data.service');
platform_browser_dynamic_1.bootstrap(app_component_1.AppComponent, [fake_data_service_1.Fake_DataService, http_1.HTTP_PROVIDERS, host_component_1.HostComponent, app_routes_1.AppRouterProviders])
    .catch(function (err) { return console.error(err); });
//# sourceMappingURL=main.js.map