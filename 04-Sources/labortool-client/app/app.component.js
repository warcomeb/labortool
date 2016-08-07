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
var navbar_component_1 = require('./navbar/navbar.component');
var home_component_1 = require('./home/home.component');
var activity_component_1 = require('./activity/activity.component');
var production_component_1 = require('./production/production.component');
var project_component_1 = require('./project/project.component');
var inventory_component_1 = require('./inventory/inventory.component');
var about_component_1 = require('./about/about.component');
var AppComponent = (function () {
    function AppComponent(router) {
        this.router = router;
    }
    AppComponent = __decorate([
        core_1.Component({
            selector: 'my-app',
            templateUrl: 'app/app.component.html',
            styleUrls: ['app/app.component.css'],
            directives: [router_1.ROUTER_DIRECTIVES, navbar_component_1.NavbarComponent, home_component_1.HomeComponent, activity_component_1.ActivityComponent, production_component_1.ProductionComponent, project_component_1.ProjectComponent, inventory_component_1.InventoryComponent, about_component_1.AboutComponent]
        }), 
        __metadata('design:paramtypes', [router_1.Router])
    ], AppComponent);
    return AppComponent;
}());
exports.AppComponent = AppComponent;
//# sourceMappingURL=app.component.js.map