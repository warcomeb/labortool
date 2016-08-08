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
var breadcrumbs_component_1 = require('../breadcrumbs/breadcrumbs.component');
var search_component_1 = require('../search/production/search.component');
var add_button_component_1 = require('../button/production/add.button.component');
var ProductionComponent = (function () {
    function ProductionComponent() {
    }
    ProductionComponent = __decorate([
        core_1.Component({
            selector: 'my-production',
            templateUrl: 'app/production/production.component.html',
            styleUrls: ['app/production/production.component.css'],
            directives: [router_1.ROUTER_DIRECTIVES, breadcrumbs_component_1.BreadcrumbsComponent, search_component_1.SearchProdComponent, add_button_component_1.AddProdBtnComponent]
        }), 
        __metadata('design:paramtypes', [])
    ], ProductionComponent);
    return ProductionComponent;
}());
exports.ProductionComponent = ProductionComponent;
//# sourceMappingURL=production.component.js.map