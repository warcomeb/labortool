import {Component, OnInit} from '@angular/core';
import {ROUTER_DIRECTIVES} from '@angular/router';
import {ActivityClass} from '../classes/classes';
import {CallsService} from '../services/calls.service';
import {BreadcrumbsComponent} from '../breadcrumbs/breadcrumbs.component';
import {SearchActivityComponent} from '../search/activity/search.activity.component';
import {AddBtnActiComponent} from '../button/activity/add.button.component';
import {Fake_DataService} from '../fake_data/fake_data.service';

@Component({
    selector: 'my-activity',
    templateUrl: 'app/activity/activity.component.html',
    styleUrls: ['app/activity/activity.component.css'],
    providers: [CallsService, Fake_DataService],
    directives: [ROUTER_DIRECTIVES, BreadcrumbsComponent, SearchActivityComponent, AddBtnActiComponent]
})

export class ActivityComponent implements OnInit {
    private serverActivitys: ActivityClass[];

    constructor(private _callsService: CallsService, private _memoryService: Fake_DataService) {
        
    }

    /*set val(val) {
        val = this.serverActivitys[0];
        return this._memoryService.getValue();
    }*/

    ngOnInit() {
        this.getActivitys();
    }

    private getActivitys(): void {
        this.serverActivitys = this._memoryService.MyActivity;
        this._callsService.GetAllActivity().subscribe(
            (activity) => {
                //this.serverActivitys = activity.json();
            },
            error => console.log(error),
            () => console.log('getActivitys complete!'));
    }

}