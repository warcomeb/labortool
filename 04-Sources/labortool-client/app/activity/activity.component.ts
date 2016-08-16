import { Component, OnInit }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { CallActivityServices }     from './calls/calls.service';
import { DataService }              from '../data/data.service';

import { ActivityClass }            from './class/activity.class';

import { SearchActivityComponent }  from './search/search.component'

@Component({
    templateUrl: './app/activity/activity.component.html',
    providers: [CallActivityServices],
    directives: [SearchActivityComponent]
})

export class ActivityComponent implements OnInit {
    private ID: number = 0;
    private ServerActivitys: ActivityClass[] = [
        { Id: 0, Name: "N/D", Description: "N/D", WorkCode: "N/D", Deadline: new Date(2016, 0, 0), Priority: 0, Status: 0, Type: 0, Employee: 0, Editable: 0, Notes: "N/D" }
    ];
    private ClientActivity: ActivityClass = {
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

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallActivityServices,
        private data: DataService) {
            this.ID = data.getID();
        }

    ngOnInit() {
        this.getActivitys();
    }

    private getActivitys(): void {
        this.calls.GetAllActivity().subscribe(
            (data) => {
                this.ServerActivitys = data.json();
            },
            error => console.log(error),
            () => console.log('getActivitys complete!'));
    }

    onSelect() {
        this.router.navigate(['/activity/add']);
    }
}