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
var calls_service_1 = require('./calls/calls.service');
var data_service_1 = require('../data/data.service');
var search_component_1 = require('./search/search.component');
var ActivityComponent = (function () {
    function ActivityComponent(route, router, calls, data) {
        this.route = route;
        this.router = router;
        this.calls = calls;
        this.data = data;
        this.ID = 0;
        this.ServerActivitys = [
            { Id: 0, Name: "N/D", Description: "N/D", WorkCode: "N/D", Deadline: new Date(2016, 0, 0), Priority: 0, Status: 0, Type: 0, Employee: 0, Editable: 0, Notes: "N/D" }
        ];
        this.ClientActivity = {
            Id: 0,
            Name: "N/D",
            Description: "N/D",
            WorkCode: "N/D",
            Deadline: new Date(2016, 0, 0),
            Priority: 0,
            Status: 0,
            Type: 0,
            Employee: 0,
            Editable: 0,
            Notes: "N/D"
        };
        this.ID = data.getID();
    }
    ActivityComponent.prototype.ngOnInit = function () {
        this.getActivitys();
    };
    ActivityComponent.prototype.getActivitys = function () {
        var _this = this;
        this.calls.GetAllActivity().subscribe(function (data) {
            _this.ServerActivitys = data.json();
        }, function (error) { return console.log(error); }, function () { return console.log('getActivitys complete!'); });
    };
    ActivityComponent.prototype.onSelect = function () {
        this.router.navigate(['/activity/add']);
    };
    ActivityComponent = __decorate([
        core_1.Component({
            templateUrl: './app/activity/activity.component.html',
            providers: [calls_service_1.CallActivityServices],
            directives: [search_component_1.SearchActivityComponent]
        }), 
        __metadata('design:paramtypes', [router_1.ActivatedRoute, router_1.Router, calls_service_1.CallActivityServices, data_service_1.DataService])
    ], ActivityComponent);
    return ActivityComponent;
}());
exports.ActivityComponent = ActivityComponent;
//# sourceMappingURL=activity.component.js.map