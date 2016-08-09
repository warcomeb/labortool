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
var data_service_1 = require('../data/data.service');
var InventoryComponent = (function () {
    function InventoryComponent(route, router, calls, data) {
        this.route = route;
        this.router = router;
        this.calls = calls;
        this.data = data;
        this.ServerComponents = [
            { Id: 0, Name: "N/D", ManufacturerName: "N/D", ManufacturerWebSite: "N/D", PartNumber: 0, DistributorName: "N/D", DistributorWebSite: "N/D", DistributorCode: "N/D", Price: 0, Code: "N/D", LocationPosition: "N/D", LocationContainer: "N/D", LocationSubContainer: "N/D", Datasheet: "N/D", FootprintName: "N/D", FootprintLink: "N/D", CategoryName: "N/D", CategoryNote: "N/D", Note: "N/D" }
        ];
        this.ID = data.getID();
    }
    InventoryComponent.prototype.ngOnInit = function () {
        this.getAllComponent();
    };
    InventoryComponent.prototype.saveID = function (ID) {
        return this.data.setID(ID);
    };
    InventoryComponent.prototype.deleteComponent = function (ID) {
        this.calls.DeleteComponent(ID).subscribe(function (error) { return console.log(error); }, function () { return console.log('DeleteComponent complete'); });
    }; // fine deleteComponent
    InventoryComponent.prototype.getAllComponent = function () {
        var _this = this;
        this.calls.GetAllComponent().subscribe(function (data) {
            _this.ServerComponents = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getAllComponent complete!'); });
    }; // fine getAllComponent
    InventoryComponent.prototype.goToAdd = function () {
        this.router.navigate(['/inventory/add']);
    };
    InventoryComponent.prototype.goToEdit = function () {
        this.router.navigate(['/inventory/edit']);
    };
    InventoryComponent.prototype.goToView = function (comp) {
        this.router.navigate(['/inventory/view', comp.Id]);
    };
    InventoryComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/inventory.component.html',
            styleUrls: ['./app/inventory/inventory.component.css'],
            providers: [calls_service_1.CallInventoryServices],
            directives: [search_component_1.SearchInventoryComponent]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallInventoryServices, data_service_1.DataService])
    ], InventoryComponent);
    return InventoryComponent;
}());
exports.InventoryComponent = InventoryComponent;
//# sourceMappingURL=inventory.component.js.map