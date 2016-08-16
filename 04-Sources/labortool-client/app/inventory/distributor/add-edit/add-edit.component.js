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
        this.ServerDistributor = {
            Id: 0,
            Name: "N/D",
            WebSite: "N/D",
        };
    }
    AddEditComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.sub = this.route.params.subscribe(function (params) {
            var id = +params['id']; // (+) converts string 'id' to a number
            _this.getSingleDistributor(id);
        });
    };
    AddEditComponent.prototype.ngOnDestroy = function () {
        this.sub.unsubscribe();
    };
    AddEditComponent.prototype.getSingleDistributor = function (id) {
        var _this = this;
        this.calls.GetSingleDistributor(id).subscribe(function (data) {
            _this.ServerDistributor = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleDistributor complete!'); });
    };
    AddEditComponent.prototype.postDistributor = function () {
        this.calls.PostDistributor(this.ClientDistributor).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('postDistributor complete!'); });
    };
    AddEditComponent.prototype.putDistributor = function (distributor) {
        this.calls.PutDistributor(distributor).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('putDistributor complete!'); });
    };
    AddEditComponent.prototype.goToDistributor = function () {
        this.router.navigate(['/inventory/distributor']);
    };
    AddEditComponent.prototype.goToView = function (distributor) {
        this.router.navigate(['/inventory/distributor/view', distributor.Id]);
    };
    AddEditComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/distributor/add-edit/add-edit.component.html',
            providers: [calls_service_1.CallDistributorServices]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallDistributorServices, data_service_1.DataService])
    ], AddEditComponent);
    return AddEditComponent;
}());
exports.AddEditComponent = AddEditComponent;
//# sourceMappingURL=add-edit.component.js.map