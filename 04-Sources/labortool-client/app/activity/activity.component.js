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
var search_activity_component_1 = require('../search/activity/search.activity.component');
var add_button_component_1 = require('../button/activity/add.button.component');
var fake_data_service_1 = require('../fake_data/fake_data.service');
var ActivityComponent = (function () {
    function ActivityComponent(_callsService, _memoryService) {
        this._callsService = _callsService;
        this._memoryService = _memoryService;
    }
    /*set val(val) {
        val = this.serverActivitys[0];
        return this._memoryService.getValue();
    }*/
    ActivityComponent.prototype.ngOnInit = function () {
        this.getActivitys();
    };
    ActivityComponent.prototype.getActivitys = function () {
        this.serverActivitys = this._memoryService.MyActivity;
        this._callsService.GetAllActivity().subscribe(function (activity) {
            //this.serverActivitys = activity.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getActivitys complete!'); });
    };
    ActivityComponent = __decorate([
        core_1.Component({
            selector: 'my-activity',
            templateUrl: 'app/activity/activity.component.html',
            styleUrls: ['app/activity/activity.component.css'],
            providers: [calls_service_1.CallsService, fake_data_service_1.Fake_DataService],
            directives: [router_1.ROUTER_DIRECTIVES, breadcrumbs_component_1.BreadcrumbsComponent, search_activity_component_1.SearchActivityComponent, add_button_component_1.AddBtnActiComponent]
        }), 
        __metadata('design:paramtypes', [calls_service_1.CallsService, fake_data_service_1.Fake_DataService])
    ], ActivityComponent);
    return ActivityComponent;
}());
exports.ActivityComponent = ActivityComponent;
//# sourceMappingURL=activity.component.js.map