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
var calls_service_2 = require('../../manufacturer/calls/calls.service');
var calls_service_3 = require('../../distributor/calls/calls.service');
var calls_service_4 = require('../../location/calls/calls.service');
var calls_service_5 = require('../../footprint/calls/calls.service');
var calls_service_6 = require('../../category/calls/calls.service');
var calls_service_7 = require('../../cat-param-type/calls/calls.service');
var calls_service_8 = require('../../unit/calls/calls.service');
var calls_service_9 = require('../../component-param/calls/calls.service');
var ViewComponent = (function () {
    function ViewComponent(route, router, data, compCalls, manuCalls, distCalls, locaCalls, footCalls, cateCalls, cptCalls, unitCalls, copaCalls) {
        this.route = route;
        this.router = router;
        this.data = data;
        this.compCalls = compCalls;
        this.manuCalls = manuCalls;
        this.distCalls = distCalls;
        this.locaCalls = locaCalls;
        this.footCalls = footCalls;
        this.cateCalls = cateCalls;
        this.cptCalls = cptCalls;
        this.unitCalls = unitCalls;
        this.copaCalls = copaCalls;
        this.ServerComponent = {
            ComponentId: 0,
            ComponentName: 'N/D',
            ComponentManufacturer: 0,
            ComponentPartNumber: 'N/D',
            ComponentDistributor: 0,
            ComponentDistributorCode: 'N/D',
            ComponentPrice: 0.00,
            ComponentCode: 'N/D',
            ComponentLocation: 0,
            ComponentDatasheet: 'N/D',
            ComponentFootprint: 0,
            ComponentCategory: 0,
            ComponentNote: 'N/D'
        };
        this.ServerManufacturer = {
            ManufacturerId: 0,
            ManufacturerName: 'N/A',
            ManufacturerWebSite: 'N/A'
        };
        this.ServerDistributor = {
            DistributorId: 0,
            DistributorName: 'N/A',
            DistributorWebSite: 'N/A'
        };
        this.ServerLocation = {
            LocationId: 0,
            LocationPosition: 'N/A',
            LocationContainer: 'N/A',
            LocationSubContainer: 'N/A'
        };
        this.ServerFootprint = {
            FootprintId: 0,
            FootprintName: 'N/A',
            FootprintLink: 'N/A'
        };
        this.ServerCategory = {
            CategoryId: 0,
            CategoryName: 'N/A',
            CategoryNote: 'N/A'
        };
        this.ServerCategoryParamType = {
            CategoryParamTypeId: 0,
            CategoryParamTypeName: 'N/A',
            CategoryParamTypeUnit: 0,
            CategoryParamTypeCategory: 0,
            CategoryParamTypeOrder: 'N/A',
            CategoryParamTypeNote: 'N/A',
        };
        this.ServerUnit = {
            UnitId: 0,
            UnitName: 'N/A',
            UnitShortName: 'N/A',
            UnitNote: 'N/A'
        };
        this.ServerComponentParam = {
            ComponentParamId: 0,
            ComponentParamComponent: 0,
            ComponentParamCategoryParamType: 0,
            ComponentParamValue: 'N/A',
            ComponentParamPrefix: this.prefix,
            ComponentParamNote: 'N/A'
        };
    }
    ViewComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.sub = this.route.params.subscribe(function (params) {
            var id = +params['id'];
            _this.getSingleComponent(id);
        });
    };
    ViewComponent.prototype.ngOnDestroy = function () {
        this.sub.unsubscribe();
    };
    ViewComponent.prototype.getSingleComponent = function (id) {
        var _this = this;
        this.compCalls.GetSingleComponent(id).subscribe(function (data) {
            _this.ServerComponent = data.json();
            _this.getSingleManufacturer(_this.ServerComponent.ComponentManufacturer);
            _this.getSingleDistributor(_this.ServerComponent.ComponentDistributor);
            _this.getSingleLocation(_this.ServerComponent.ComponentLocation);
            _this.getSingleFootprint(_this.ServerComponent.ComponentFootprint);
            _this.getSingleCategory(_this.ServerComponent.ComponentCategory);
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleComponent complete!'); });
    };
    ViewComponent.prototype.getSingleManufacturer = function (id) {
        var _this = this;
        this.manuCalls.GetSingleManufacturer(id).subscribe(function (data) {
            _this.ServerManufacturer = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleManufacturer complete!'); });
    };
    ViewComponent.prototype.getSingleDistributor = function (id) {
        var _this = this;
        this.distCalls.GetSingleDistributor(id).subscribe(function (data) {
            _this.ServerDistributor = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleDistributor complete!'); });
    };
    ViewComponent.prototype.getSingleLocation = function (id) {
        var _this = this;
        this.locaCalls.GetSingleLocation(id).subscribe(function (data) {
            _this.ServerLocation = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleLocation complete!'); });
    };
    ViewComponent.prototype.getSingleFootprint = function (id) {
        var _this = this;
        this.footCalls.GetSingleFootprint(id).subscribe(function (data) {
            _this.ServerFootprint = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleFootprint complete!'); });
    };
    ViewComponent.prototype.getSingleCategory = function (id) {
        var _this = this;
        this.cateCalls.GetSingleCategory(id).subscribe(function (data) {
            _this.ServerCategory = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleCategory complete!'); });
    };
    ViewComponent.prototype.getSingleCategoryParamType = function (id) {
        var _this = this;
        this.cptCalls.GetSingleCatParamType(id).subscribe(function (data) {
            _this.ServerCategoryParamType = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleCategoryParamType complete!'); });
    };
    ViewComponent.prototype.getSingleUnit = function (id) {
        var _this = this;
        this.unitCalls.GetSingleUnit(id).subscribe(function (data) {
            _this.ServerUnit = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleCategory complete!'); });
    };
    ViewComponent.prototype.getSingleComponentParam = function (id) {
        var _this = this;
        this.copaCalls.GetSingleComponentParam(id).subscribe(function (data) {
            _this.ServerComponentParam = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleComponentParam complete!'); });
    };
    ViewComponent.prototype.deleteComponent = function (comp) {
        this.compCalls.DeleteComponent(comp.ComponentId).subscribe(function (error) { return console.log(error); }, function () { return console.log('deleteComponent complete!'); });
    };
    ViewComponent.prototype.goToComponent = function () {
        this.router.navigate(['/inventory/component']);
    };
    ViewComponent.prototype.goToEdit = function (comp) {
        this.router.navigate(['/inventory/component/edit', comp.ComponentId]);
    };
    ViewComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/component/view/view.component.html',
            styleUrls: ['./app/inventory/component/view/view.component.css'],
            providers: [calls_service_1.CallComponentServices,
                calls_service_2.CallManufacturerServices,
                calls_service_3.CallDistributorServices,
                calls_service_4.CallLocationServices,
                calls_service_5.CallFootprintServices,
                calls_service_6.CallCategoryServices,
                calls_service_7.CallCatParamTypeServices,
                calls_service_8.CallUnitServices,
                calls_service_9.CallComponentParamServices]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, data_service_1.DataService, calls_service_1.CallComponentServices, calls_service_2.CallManufacturerServices, calls_service_3.CallDistributorServices, calls_service_4.CallLocationServices, calls_service_5.CallFootprintServices, calls_service_6.CallCategoryServices, calls_service_7.CallCatParamTypeServices, calls_service_8.CallUnitServices, calls_service_9.CallComponentParamServices])
    ], ViewComponent);
    return ViewComponent;
}());
exports.ViewComponent = ViewComponent;
//# sourceMappingURL=view.component.js.map