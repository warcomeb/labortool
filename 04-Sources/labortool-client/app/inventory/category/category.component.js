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
var search_component_1 = require('./search/search.component');
var calls_service_1 = require('./calls/calls.service');
var data_service_1 = require('../../data/data.service');
var CategoryComponent = (function () {
    function CategoryComponent(route, router, calls, data) {
        this.route = route;
        this.router = router;
        this.calls = calls;
        this.data = data;
        this.ServerCategorys = [
            { CategoryId: 0, CategoryName: 'N/D', CategoryNote: 'N/D' }
        ];
    }
    CategoryComponent.prototype.ngOnInit = function () {
        this.getAllCategory();
    };
    CategoryComponent.prototype.getAllCategory = function () {
        var _this = this;
        this.calls.GetAllCategory().subscribe(function (data) {
            _this.ServerCategorys = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getAllCategory complete!'); });
    };
    CategoryComponent.prototype.goToAdd = function () {
        this.router.navigate(['/inventory/category/add']);
    };
    CategoryComponent.prototype.goToView = function (category) {
        this.router.navigate(['/inventory/category/view', category.CategoryId]);
    };
    CategoryComponent = __decorate([
        core_1.Component({
            templateUrl: './app/inventory/category/category.component.html',
            providers: [calls_service_1.CallCategoryServices],
            directives: [search_component_1.SearchCategoryComponent]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallCategoryServices, data_service_1.DataService])
    ], CategoryComponent);
    return CategoryComponent;
}());
exports.CategoryComponent = CategoryComponent;
//# sourceMappingURL=category.component.js.map