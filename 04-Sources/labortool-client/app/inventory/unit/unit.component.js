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
var router_1 = require('@angular/router');
var search_component_1 = require('./search/search.component');
var calls_service_1 = require('./calls/calls.service');
var data_service_1 = require('../../data/data.service');
var UnitComponent = (function () {
    function UnitComponent(route, router, calls, data) {
        this.route = route;
        this.router = router;
        this.calls = calls;
        this.data = data;
        this.ServerUnits = [
            { Id: 0, Name: "N/D", ShortName: "N/D", Note: "N/D" }
        ];
    }
    UnitComponent.prototype.ngOnInit = function () {
        this.getAllUnit();
    };
    UnitComponent.prototype.getAllUnit = function () {
        var _this = this;
        this.calls.GetAllUnit().subscribe(function (data) {
            _this.ServerUnits = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getAllUnit complete!'); });
    };
    UnitComponent.prototype.goToView = function (unit) {
        this.router.navigate(['/inventory/unit/view', unit.Id]);
    };
    UnitComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/unit/unit.component.html',
            providers: [calls_service_1.CallUnitServices],
            directives: [search_component_1.SearchUnitComponent]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallUnitServices, data_service_1.DataService])
    ], UnitComponent);
    return UnitComponent;
}());
exports.UnitComponent = UnitComponent;
//# sourceMappingURL=unit.component.js.map