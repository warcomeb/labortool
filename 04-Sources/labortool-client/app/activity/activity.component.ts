import {Component, OnInit} from '@angular/core';
import {ROUTER_DIRECTIVES, Router} from '@angular/router';
import {ActiClass} from '../classes/classes';
import {CallsService} from '../services/calls.service';
import {BreadcrumbsComponent} from '../breadcrumbs/breadcrumbs.component';
import {SearchActiComponent} from '../search/activity/search.component';
import {AddActiBtnComponent} from '../button/activity/add.button.component';
import {MemoryDataService} from '../services/memory.data.service';

@Component({
    selector: 'my-activity',
    templateUrl: 'app/activity/activity.component.html',
    styleUrls: ['app/activity/activity.component.css'],
    providers: [CallsService],
    directives: [ROUTER_DIRECTIVES, BreadcrumbsComponent, SearchActiComponent, AddActiBtnComponent]
})

export class ActivityComponent implements OnInit {
    private serverActivitys: ActiClass[];

    constructor(private router: Router, private _callsService:CallsService, private _memoryDataService:MemoryDataService) {
    }

    ngOnInit() {
        this.getActivitys();
    }

    private getActivitys():void {
        //this.serverActivitys = this._memoryService.MyActivity;
        this._callsService.GetAllActivity().subscribe(
            (activity) => {
                this.serverActivitys = activity.json();
            },
            error => console.log(error),
            () => console.log('getActivitys complete!'));
    }

}