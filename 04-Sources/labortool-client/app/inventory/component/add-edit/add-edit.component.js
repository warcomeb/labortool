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
        this.ServerComponent = {
            Id: 0,
            Name: "N/D",
            ManufacturerName: "N/D",
            ManufacturerWebSite: "N/D",
            PartNumber: 0,
            DistributorName: "N/D",
            DistributorWebSite: "N/D",
            DistributorCode: "N/D",
            Price: 0.00,
            Code: "N/D",
            LocationPosition: "N/D",
            LocationContainer: "N/D",
            LocationSubContainer: "N/D",
            Datasheet: "N/D",
            FootprintName: "N/D",
            FootprintLink: "N/D",
            CategoryName: "N/D",
            CategoryNote: "N/D",
            Note: "N/D"
        };
    }
    AddEditComponent.prototype.ngOnInit = function () {
        var _this = this;
        this.sub = this.route.params.subscribe(function (params) {
            var id = +params['id']; // (+) converts string 'id' to a number
            _this.getSingleComponent(id);
        });
    };
    AddEditComponent.prototype.ngOnDestroy = function () {
        this.sub.unsubscribe();
    };
    AddEditComponent.prototype.getSingleComponent = function (id) {
        var _this = this;
        this.calls.GetSingleComponent(id).subscribe(function (data) {
            _this.ServerComponent = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getSingleComponent complete!'); });
    };
    AddEditComponent.prototype.postComponent = function () {
        this.calls.PostComponent(this.ClientComponent).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('postComponent complete!'); });
    };
    AddEditComponent.prototype.putComponent = function (comp) {
        this.calls.PutComponent(comp).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('putComponent complete!'); });
    };
    AddEditComponent.prototype.goToInventory = function () {
        this.router.navigate(['/inventory']);
    };
    AddEditComponent.prototype.goToView = function (comp) {
        this.router.navigate(['/inventory', comp.Id]);
    };
    AddEditComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/add-edit/add-edit.component.html',
            providers: [calls_service_1.CallInventoryServices]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallInventoryServices, data_service_1.DataService])
    ], AddEditComponent);
    return AddEditComponent;
}());
exports.AddEditComponent = AddEditComponent;
//# sourceMappingURL=add-edit.component.js.map