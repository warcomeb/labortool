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
var search_component_1 = require('../search/project/search.component');
var add_button_component_1 = require('../button/project/add.button.component');
var ProjectComponent = (function () {
    function ProjectComponent() {
    }
    ProjectComponent = __decorate([
        core_1.Component({
            selector: 'component-project',
            templateUrl: 'app/project/project.component.html',
            styleUrls: ['app/project/project.component.css'],
            directives: [router_1.ROUTER_DIRECTIVES, breadcrumbs_component_1.BreadcrumbsComponent, search_component_1.SearchProjComponent, add_button_component_1.AddProjBtnComponent]
        }), 
        __metadata('design:paramtypes', [])
    ], ProjectComponent);
    return ProjectComponent;
}());
exports.ProjectComponent = ProjectComponent;
//# sourceMappingURL=project.component.js.map