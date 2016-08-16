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
var ManufacturerComponent = (function () {
    function ManufacturerComponent(route, router, calls, data) {
        this.route = route;
        this.router = router;
        this.calls = calls;
        this.data = data;
        this.ServerManufacturers = [
            { Id: 0, Name: "N/D", WebSite: "N/D" }
        ];
    }
    ManufacturerComponent.prototype.ngOnInit = function () {
        this.getAllManufacturer();
    };
    ManufacturerComponent.prototype.getAllManufacturer = function () {
        var _this = this;
        this.calls.GetAllManufacturer().subscribe(function (data) {
            _this.ServerManufacturers = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getAllManufacturer complete!'); });
    }; // fine getAllComponent
    ManufacturerComponent.prototype.goToAdd = function () {
        this.router.navigate(['/inventory/manufacturer/add']);
    };
    ManufacturerComponent.prototype.goToEdit = function () {
        this.router.navigate(['/inventory/manufacturer/edit']);
    };
    ManufacturerComponent.prototype.goToView = function (comp) {
        this.router.navigate(['/inventory/manufacturer/view', comp.Id]);
    };
    ManufacturerComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/manufacturer/manufacturer.component.html',
            providers: [calls_service_1.CallInventoryServices],
            directives: [search_component_1.SearchManufacturerComponent]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallInventoryServices, data_service_1.DataService])
    ], ManufacturerComponent);
    return ManufacturerComponent;
}());
exports.ManufacturerComponent = ManufacturerComponent;
//# sourceMappingURL=manufacturer.component.js.map