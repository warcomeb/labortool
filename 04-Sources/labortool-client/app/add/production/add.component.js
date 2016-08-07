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
var calls_service_1 = require('../../services/calls.service');
var AddProdComponent = (function () {
    function AddProdComponent(_callsService) {
        this._callsService = _callsService;
    }
    AddProdComponent.prototype.postProduction = function () {
        this._callsService.PostProduction(this.MyProduction).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('AddProduction complete!'); });
    };
    AddProdComponent = __decorate([
        core_1.Component({
            selector: 'add-prod',
            templateUrl: 'app/add/production/add.component.html',
            styleUrls: ['app/add/add.component.css'],
            providers: [calls_service_1.CallsService]
        }), 
        __metadata('design:paramtypes', [calls_service_1.CallsService])
    ], AddProdComponent);
    return AddProdComponent;
}());
exports.AddProdComponent = AddProdComponent;
;
//# sourceMappingURL=add.component.js.map