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
var AddActivityComponent = (function () {
    function AddActivityComponent(_callsService) {
        this._callsService = _callsService;
        this.MyActivity = {
            Id: 0,
            Title: "",
            Description: "",
            WorkCode: "",
            Deadline: new Date(0, 0, 0),
            Priority: 0,
            Status: 0,
            Type: 0,
            Employee: 0,
            Editable: 0,
            Notes: ""
        };
    }
    AddActivityComponent.prototype.AddActivity = function () {
        this._callsService.PostAnActivity(this.MyActivity).subscribe(function (data) { return console.log(data); }, function (error) { return console.log(error); }, function () { return console.log('AddActivity complete!'); });
    };
    AddActivityComponent = __decorate([
        core_1.Component({
            selector: 'my-add-component',
            templateUrl: 'app/add/activity/add.activity.component.html',
            styleUrls: ['app/add/activity/add.activity.component.css'],
            providers: [calls_service_1.CallsService]
        }), 
        __metadata('design:paramtypes', [calls_service_1.CallsService])
    ], AddActivityComponent);
    return AddActivityComponent;
}());
exports.AddActivityComponent = AddActivityComponent;
//# sourceMappingURL=add.activity.component.js.map