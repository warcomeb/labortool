"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
var core_1 = require('@angular/core');
var http_1 = require('@angular/http');
var connection_service_1 = require('../../../connection/connection.service');
var CallDistributorServices = (function () {
    function CallDistributorServices(http, host) {
        var _this = this;
        this.http = http;
        this.host = host;
        this.GetAllDistributor = function () {
            return _this.http.get(_this.URL + '/inventory/distributor');
        };
        this.GetSingleDistributor = function (id) {
            return _this.http.get(_this.URL + '/inventory/distributor/' + id);
        };
        this.PostDistributor = function (item) {
            var toAdd = JSON.stringify({ Item: item });
            return _this.http.post(_this.URL + '/inventory/distributor', toAdd, { headers: _this.headers });
        };
        this.PutDistributor = function (item) {
            return _this.http.put(_this.URL + '/inventory/distributor', JSON.stringify(item), { headers: _this.headers });
        };
        this.DeleteDistributor = function (id) {
            return _this.http.delete(_this.URL + '/inventory/distributor/' + id);
        };
        this.URL = host.serverURL;
        this.headers = new http_1.Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }
    CallDistributorServices = __decorate([
        core_1.Injectable(), 
        __metadata('design:paramtypes', [http_1.Http, connection_service_1.ConnectionService])
    ], CallDistributorServices);
    return CallDistributorServices;
}());
exports.CallDistributorServices = CallDistributorServices;
//# sourceMappingURL=calls.service.js.map