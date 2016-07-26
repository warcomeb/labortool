import {Component, OnInit} from '@angular/core';
import {ROUTER_DIRECTIVES} from '@angular/router';
import {ClassActivity} from '../classes/activity.class';
import {CallsService} from '../services/calls.service';
import {MemoryService} from '../services/memory.service';
import {BreadcrumbsComponent} from '../breadcrumbs/breadcrumbs.component';
import {SearchActivityComponent} from '../search/activity/search.activity.component';
import {AddButtonComponent} from '../button/add.button.component';

@Component({
    selector: 'my-activity',
    templateUrl: 'app/activity/activity.component.html',
    styleUrls: ['app/activity/activity.component.css'],
    providers: [CallsService],
    directives: [ROUTER_DIRECTIVES, BreadcrumbsComponent, SearchActivityComponent, AddButtonComponent]
})

export class ActivityComponent implements OnInit {
    private serverActivitys: ClassActivity[];

    constructor(private _callsService: CallsService, private _memoryService: MemoryService) {
        
    }

    /*set val(val) {
        val = this.serverActivitys[0];
        return this._memoryService.getValue();
    }*/

    ngOnInit() {
        this.getActivitys();
    }

    private getActivitys(): void {
        this._callsService.GetAllActivity().subscribe(
        (activity) => {
            this.serverActivitys = activity.json();
        },
        error => console.log(error),
        () => console.log('getActivitys complete!'));
    }

}