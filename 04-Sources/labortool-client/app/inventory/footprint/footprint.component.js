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
var FootprintComponent = (function () {
    function FootprintComponent(route, router, calls, data) {
        this.route = route;
        this.router = router;
        this.calls = calls;
        this.data = data;
        this.ServerFootprints = [
            { FootprintId: 0, FootprintName: 'N/D', FootprintLink: 'N/D' }
        ];
    }
    FootprintComponent.prototype.ngOnInit = function () {
        this.getAllFootprint();
    };
    FootprintComponent.prototype.getAllFootprint = function () {
        var _this = this;
        this.calls.GetAllFootprint().subscribe(function (data) {
            _this.ServerFootprints = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getAllFootprint complete!'); });
    };
    FootprintComponent.prototype.goToAdd = function () {
        this.router.navigate(['/inventory/footprint/add']);
    };
    FootprintComponent.prototype.goToView = function (footprint) {
        this.router.navigate(['/inventory/footprint/view', footprint.FootprintId]);
    };
    FootprintComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/footprint/footprint.component.html',
            providers: [calls_service_1.CallFootprintServices],
            directives: [search_component_1.SearchFootprintComponent]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallFootprintServices, data_service_1.DataService])
    ], FootprintComponent);
    return FootprintComponent;
}());
exports.FootprintComponent = FootprintComponent;
//# sourceMappingURL=footprint.component.js.map