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
var data_service_1 = require('../../../data/data.service');
var calls_service_1 = require('../calls/calls.service');
var calls_service_2 = require('../../category/calls/calls.service');
var calls_service_3 = require('../../unit/calls/calls.service');
var ViewComponent = (function () {
    function ViewComponent(route, router, data, cptCalls, unitCalls, cateCalls) {
        this.route = route;
        this.router = router;
        this.data = data;
        this.cptCalls = cptCalls;
        this.unitCalls = unitCalls;
        this.cateCalls = cateCalls;
        this.ServerCategoryParamType = {
            CategoryParamTypeId: 0,
            CategoryParamTypeName: 'N/D',
            CategoryParamTypeCategory: 0,
            CategoryParamTypeUnit: 0,
            CategoryParamTypeOrder: 'N/D',
            CategoryParamTypeNote: 'N/D'
        };
        this.ServerCategory = {
            CategoryId: 0,
            CategoryName: 'N/D',
            CategoryNote: 'N/D'
        };
        this.ServerUnit = {
            UnitId: 0,
            UnitName: 'N/D',
            UnitShortName: 'N/D',
            UnitNote: 'N/D'
        };
    }
    ViewComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.sub = this.route.params.subscribe(function (params) {
            var id = +params['id']; // (+) converts string 'id' to a number
            _this.getSingleCatParamType(id);
        });
    };
    ViewComponent.prototype.ngOnDestroy = function () {
        this.sub.unsubscribe();
    };
    ViewComponent.prototype.getSingleCatParamType = function (id) {
        var _this = this;
        this.cptCalls.GetSingleCatParamType(id).subscribe(function (data) {
            _this.ServerCategoryParamType = data.json();
            _this.getSingleCategory(_this.ServerCategoryParamType.CategoryParamTypeCategory);
            _this.getSingleUnit(_this.ServerCategoryParamType.CategoryParamTypeUnit);
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleCatParamType complete!'); });
    };
    ViewComponent.prototype.getSingleCategory = function (id) {
        var _this = this;
        this.cateCalls.GetSingleCategory(id).subscribe(function (data) {
            _this.ServerCategory = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleCategory complete!'); });
    };
    ViewComponent.prototype.getSingleUnit = function (id) {
        var _this = this;
        this.unitCalls.GetSingleUnit(id).subscribe(function (data) {
            _this.ServerUnit = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleUnit complete!'); });
    };
    ViewComponent.prototype.goToCatParamType = function () {
        this.router.navigate(['/inventory/category_parameter_type']);
    };
    ViewComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/cat-param-type/view/view.component.html',
            styleUrls: ['./app/inventory/cat-param-type/view/view.component.css'],
            providers: [calls_service_1.CallCatParamTypeServices, calls_service_2.CallCategoryServices, calls_service_3.CallUnitServices]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, data_service_1.DataService, calls_service_1.CallCatParamTypeServices, calls_service_3.CallUnitServices, calls_service_2.CallCategoryServices])
    ], ViewComponent);
    return ViewComponent;
}());
exports.ViewComponent = ViewComponent;
//# sourceMappingURL=view.component.js.map