"use strict";
var platform_browser_dynamic_1 = require('@angular/platform-browser-dynamic');
var http_1 = require('@angular/http');
var host_component_1 = require('./configs/host.component');
var app_component_1 = require('./app.component');
var app_routes_1 = require('./app.routes');
var memory_data_service_1 = require('./services/memory.data.service');
platform_browser_dynamic_1.bootstrap(app_component_1.AppComponent, [app_routes_1.appRouterProviders, memory_data_service_1.MemoryDataService, http_1.HTTP_PROVIDERS, host_component_1.HostComponent])
    .catch(function (err) { return console.error(err); });
//# sourceMappingURL=main.js.map