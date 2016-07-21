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
var host_component_1 = require('../configs/host.component');
var CallsService = (function () {
    function CallsService(_http, _host) {
        var _this = this;
        this._http = _http;
        this._host = _host;
        this.numeroID = 0;
        /* Get calls */
        this.GetAll = function () {
            return _this._http.get(_this.actionURL);
        };
        this.GetAllActivity = function () {
            return _this._http.get(_this.actionURL + '/activity');
        };
        this.GetActivity = function () {
            return _this._http.get(_this.actionURL + '/activity/?id=' + _this.numeroID);
        };
        // mai provata
        this.GetSingle = function (id) {
            return _this._http.get(_this.actionURL + id);
        };
        // mai provata
        this.POST = function (itemName) {
            var toAdd = JSON.stringify({ ItemName: itemName });
            return _this._http.post(_this.actionURL, toAdd, { headers: _this.headers });
        };
        this.PUT = function (itemToUpdate) {
            return _this._http.put(_this.actionURL, JSON.stringify(itemToUpdate), { headers: _this.headers });
        };
        // mai provata
        this.DELETE = function (id) {
            return _this._http.delete(_this.actionURL + id);
        };
        this.actionURL = _host.serverURL;
        this.headers = new http_1.Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }
    CallsService = __decorate([
        core_1.Injectable(), 
        __metadata('design:paramtypes', [http_1.Http, host_component_1.HostComponent])
    ], CallsService);
    return CallsService;
}());
exports.CallsService = CallsService;
//# sourceMappingURL=calls.service.js.map