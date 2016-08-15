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
var AddEditComponent = (function () {
    function AddEditComponent(route, router, calls, data) {
        this.route = route;
        this.router = router;
        this.calls = calls;
        this.data = data;
        this.ServerLocation = {
            Id: 0,
            Position: "N/D",
            Container: "N/D",
            SubContainer: "N/D"
        };
    }
    AddEditComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.sub = this.route.params.subscribe(function (params) {
            var id = +params['id']; // (+) converts string 'id' to a number
            _this.getSingleLocation(id);
        });
    };
    AddEditComponent.prototype.ngOnDestroy = function () {
        this.sub.unsubscribe();
    };
    AddEditComponent.prototype.getSingleLocation = function (id) {
        var _this = this;
        this.calls.GetSingleLocation(id).subscribe(function (data) {
            _this.ServerLocation = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleLocation complete!'); });
    };
    AddEditComponent.prototype.postLocation = function () {
        this.calls.PostLocation(this.ClientLocation).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('postLocation complete!'); });
    };
    AddEditComponent.prototype.putLocation = function (location) {
        this.calls.PutLocation(location).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('putLocation complete!'); });
    };
    AddEditComponent.prototype.goToLocation = function () {
        this.router.navigate(['/inventory/location']);
    };
    AddEditComponent.prototype.goToView = function (location) {
        this.router.navigate(['/inventory/location/view', location.Id]);
    };
    AddEditComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/location/add-edit/add-edit.component.html',
            providers: [calls_service_1.CallLocationServices]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallLocationServices, data_service_1.DataService])
    ], AddEditComponent);
    return AddEditComponent;
}());
exports.AddEditComponent = AddEditComponent;
//# sourceMappingURL=add-edit.component.js.map