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
var Fake_DataService = (function () {
    function Fake_DataService() {
        this.MyActivity = [
            { Id: 1, Title: 'prova', Description: 'prova1', WorkCode: '1234', Deadline: new Date(2016, 0, 0), Priority: 3, Status: 5, Type: 3, Employee: 1, Editable: 1, Notes: 'sadadsa' }
        ];
    }
    Fake_DataService = __decorate([
        core_1.Injectable(), 
        __metadata('design:paramtypes', [])
    ], Fake_DataService);
    return Fake_DataService;
}());
exports.Fake_DataService = Fake_DataService;
//# sourceMappingURL=fake_data.service.js.map