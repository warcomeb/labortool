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
var calls_service_1 = require('../services/calls.service');
var breadcrumbs_component_1 = require('../breadcrumbs/breadcrumbs.component');
var search_component_1 = require('../search/inventory/search.component');
var add_button_component_1 = require('../button/inventory/add.button.component');
var memory_data_service_1 = require('../services/memory.data.service');
var InventoryComponent = (function () {
    function InventoryComponent(router, _callsService, _memoryDataService) {
        this.router = router;
        this._callsService = _callsService;
        this._memoryDataService = _memoryDataService;
        this.prova = 100000;
    }
    InventoryComponent.prototype.ngOnInit = function () {
        this.getAllComponent();
    };
    InventoryComponent.prototype.saveID = function (ID) {
        return this._memoryDataService.setID(ID);
    };
    InventoryComponent.prototype.deleteComponent = function (ID) {
        this._callsService.DeleteComponent(ID).subscribe(function (error) { return console.log(error); }, function () { return console.log('DeleteComponent complete'); });
    }; // fine deleteComponent
    InventoryComponent.prototype.getAllComponent = function () {
        var _this = this;
        this._callsService.GetAllComponent().subscribe(function (component) {
            _this.ServerComponents = component.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getAllComponent complete!'); });
    }; // fine getAllComponent
    InventoryComponent = __decorate([
        core_1.Component({
            selector: 'my-inventory',
            templateUrl: 'app/inventory/inventory.component.html',
            styleUrls: ['app/inventory/inventory.component.css'],
            directives: [router_1.ROUTER_DIRECTIVES, breadcrumbs_component_1.BreadcrumbsComponent, search_component_1.SearchInveComponent, add_button_component_1.AddInveBtnComponent],
            providers: [calls_service_1.CallsService]
        }), 
        __metadata('design:paramtypes', [router_1.Router, calls_service_1.CallsService, memory_data_service_1.MemoryDataService])
    ], InventoryComponent);
    return InventoryComponent;
}());
exports.InventoryComponent = InventoryComponent;
//# sourceMappingURL=inventory.component.js.map