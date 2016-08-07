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
var search_component_1 = require('../search/activity/search.component');
var add_button_component_1 = require('../button/activity/add.button.component');
var memory_data_service_1 = require('../services/memory.data.service');
var ActivityComponent = (function () {
    function ActivityComponent(router, _callsService, _memoryDataService) {
        this.router = router;
        this._callsService = _callsService;
        this._memoryDataService = _memoryDataService;
    }
    ActivityComponent.prototype.ngOnInit = function () {
        this.getActivitys();
    };
    ActivityComponent.prototype.getActivitys = function () {
        var _this = this;
        //this.serverActivitys = this._memoryService.MyActivity;
        this._callsService.GetAllActivity().subscribe(function (activity) {
            _this.serverActivitys = activity.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getActivitys complete!'); });
    };
    ActivityComponent = __decorate([
        core_1.Component({
            selector: 'my-activity',
            templateUrl: 'app/activity/activity.component.html',
            styleUrls: ['app/activity/activity.component.css'],
            providers: [calls_service_1.CallsService],
            directives: [router_1.ROUTER_DIRECTIVES, breadcrumbs_component_1.BreadcrumbsComponent, search_component_1.SearchActiComponent, add_button_component_1.AddActiBtnComponent]
        }), 
        __metadata('design:paramtypes', [router_1.Router, calls_service_1.CallsService, memory_data_service_1.MemoryDataService])
    ], ActivityComponent);
    return ActivityComponent;
}());
exports.ActivityComponent = ActivityComponent;
//# sourceMappingURL=activity.component.js.map