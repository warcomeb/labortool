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
        // example
        /*public GetAll = (): Observable<Response> => {
            return this._http.get(this.actionURL);
        }*/
        /* GetAll calls */
        this.GetAllActivity = function () {
            return _this._http.get(_this.actionURL + '/activity');
        };
        this.GetAllProduction = function () {
            return _this._http.get(_this.actionURL + '/activity');
        };
        this.GetAllProject = function () {
            return _this._http.get(_this.actionURL + '/activity');
        };
        this.GetAllComponent = function () {
            return _this._http.get(_this.actionURL + '/inventory');
        };
        // example
        /*public GetSingle = (id:number): Observable<Response> => {
            return this._http.get(this.actionURL + id);
        }*/
        /* GetSingle calls */
        this.GetSingleActivity = function (id) {
            return _this._http.get(_this.actionURL + '/activity' + id);
        };
        this.GetSingleProduction = function (id) {
            return _this._http.get(_this.actionURL + '/production' + id);
        };
        this.GetSingleProject = function (id) {
            return _this._http.get(_this.actionURL + '/project' + id);
        };
        this.GetSingleComponent = function (id) {
            return _this._http.get(_this.actionURL + '/component' + id);
        };
        // example
        /*public POST = (itemName: string): Observable<Response> => {
            var toAdd = JSON.stringify({ItemName: itemName});
            return this._http.post(this.actionURL, toAdd, {headers:this.headers});
        }*/
        /* Post Calls */
        this.PostActivity = function (item) {
            var toAdd = JSON.stringify({ Item: item });
            return _this._http.post(_this.actionURL + '/activity', toAdd, { headers: _this.headers });
        };
        this.PostProduction = function (item) {
            var toAdd = JSON.stringify({ Item: item });
            return _this._http.post(_this.actionURL + '/production', toAdd, { headers: _this.headers });
        };
        this.PostComponent = function (item) {
            var toAdd = JSON.stringify({ Item: item });
            return _this._http.post(_this.actionURL + '/inventory', toAdd, { headers: _this.headers });
        };
        this.PostProject = function (item) {
            var toAdd = JSON.stringify({ Item: item });
            return _this._http.post(_this.actionURL + '/project', toAdd, { headers: _this.headers });
        };
        // example
        /*public PUT = (itemToUpdate:string):Observable<Response> => {
            return this._http.put(this.actionURL, JSON.stringify(itemToUpdate), { headers: this.headers });
        }*/
        /* Put Calls */
        this.PutActivity = function (item) {
            return _this._http.put(_this.actionURL, JSON.stringify(item), { headers: _this.headers });
        };
        this.PutProduction = function (item) {
            return _this._http.put(_this.actionURL, JSON.stringify(item), { headers: _this.headers });
        };
        this.PutProject = function (item) {
            return _this._http.put(_this.actionURL, JSON.stringify(item), { headers: _this.headers });
        };
        this.PutComponent = function (item) {
            return _this._http.put(_this.actionURL, JSON.stringify(item), { headers: _this.headers });
        };
        // example
        /*public DELETE = (id: number): Observable<Response> => {
                return this._http.delete(this.actionURL + id);
        }*/
        /* Delete Calls */
        this.DeleteActivity = function (id) {
            return _this._http.delete(_this.actionURL + '/activity' + id);
        };
        this.DeleteProduction = function (id) {
            return _this._http.delete(_this.actionURL + '/production' + id);
        };
        this.DeleteProject = function (id) {
            return _this._http.delete(_this.actionURL + '/project' + id);
        };
        this.DeleteComponent = function (id) {
            return _this._http.delete(_this.actionURL + '/inventory' + id);
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