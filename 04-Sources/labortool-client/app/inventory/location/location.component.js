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
var LocationComponent = (function () {
    function LocationComponent(route, router, calls, data) {
        this.route = route;
        this.router = router;
        this.calls = calls;
        this.data = data;
        this.ServerLocations = [
            { Id: 0, Position: "N/D", Container: "N/D", SubContainer: "N/D" }
        ];
    }
    LocationComponent.prototype.ngOnInit = function () {
        this.getAllLocation();
    };
    LocationComponent.prototype.getAllLocation = function () {
        var _this = this;
        this.calls.GetAllLocation().subscribe(function (data) {
            _this.ServerLocations = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getAllLocation complete!'); });
    }; // fine getAllComponent
    LocationComponent.prototype.goToAdd = function () {
        this.router.navigate(['/inventory/location/add']);
    };
    LocationComponent.prototype.goToEdit = function () {
        this.router.navigate(['/inventory/location/edit']);
    };
    LocationComponent.prototype.goToView = function (location) {
        this.router.navigate(['/inventory/location/view', location.Id]);
    };
    LocationComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/location/location.component.html',
            providers: [calls_service_1.CallLocationServices],
            directives: [search_component_1.SearchLocationComponent]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallLocationServices, data_service_1.DataService])
    ], LocationComponent);
    return LocationComponent;
}());
exports.LocationComponent = LocationComponent;
//# sourceMappingURL=location.component.js.map