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
var calls_service_1 = require('../../services/calls.service');
var memory_data_service_1 = require('../../services/memory.data.service');
var AddInveComponent = (function () {
    function AddInveComponent(router, _callsService, _memoryDataService) {
        this.router = router;
        this._callsService = _callsService;
        this._memoryDataService = _memoryDataService;
        this.ID = 0;
        this.ServerComponent = {
            Id: 0,
            Name: "",
            ManufacturerName: "",
            ManufacturerWebSite: "",
            PartNumber: 0,
            DistributorName: "",
            DistributorWebSite: "",
            DistributorCode: "",
            Price: 0.00,
            Code: "",
            LocationPosition: "",
            LocationContainer: "",
            LocationSubContainer: "",
            Datasheet: "",
            FootprintName: "",
            FootprintLink: "",
            CategoryName: "",
            CategoryNote: "",
            Note: ""
        };
        this.ID = _memoryDataService.getID();
    }
    AddInveComponent.prototype.ngOnInit = function () {
        if (this.ID > 0) {
            this.getSingleComponent(this.ID);
        }
    };
    AddInveComponent.prototype.getSingleComponent = function (id) {
        var _this = this;
        this._callsService.GetSingleComponent(id).subscribe(function (component) {
            _this.ServerComponent = component.json();
        }, function (error) { return console.log(error); }, function () { return console.log(_this.ID); });
    };
    AddInveComponent.prototype.postComponent = function () {
        this._callsService.PostComponent(this.ClientComponent).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('postComponent complete!'); });
    };
    AddInveComponent.prototype.putComponent = function (id) {
        this._callsService.PutComponent(this.ClientComponent).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('putComponent complete!'); });
        this._memoryDataService.setID(0);
    };
    AddInveComponent = __decorate([
        core_1.Component({
            selector: 'add-inve',
            templateUrl: 'app/add/inventory/add.component.html',
            styleUrls: ['app/add/add.component.css'],
            providers: [calls_service_1.CallsService],
            directives: [router_1.ROUTER_DIRECTIVES]
        }), 
        __metadata('design:paramtypes', [router_1.Router, calls_service_1.CallsService, memory_data_service_1.MemoryDataService])
    ], AddInveComponent);
    return AddInveComponent;
}());
exports.AddInveComponent = AddInveComponent;
;
//# sourceMappingURL=add.component.js.map