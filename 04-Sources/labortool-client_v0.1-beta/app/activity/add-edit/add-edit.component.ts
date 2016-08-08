import { Component, OnInit }               from '@angular/core';
import { Router, ActivatedRoute }  from '@angular/router';

import { DataService }             from '../../data/data.service';
import { CallActivityServices }    from '../calls/calls.service';

import { ActivityClass }          from '../class/activity.class';

@Component({
    templateUrl: './app/activity/add-edit/add-edit.component.html',
    providers: [CallActivityServices]
})

export class AddEditComponent implements OnInit { 
    private ID: number = 0;
    private ServerActivity: ActivityClass = {
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
        if (this.ID > 0) {
            this.getSingleActivity(this.ID);
        }

    }

    getSingleActivity(id: number) {
        this.calls.GetSingleActivity(id).subscribe(
            (data) => {
                this.ServerActivity = data.json();
            },
            error => console.log(error),
            () => console.log(this.ID)
        );
    }

    postActivity() {
        this.calls.PostActivity(this.ClientActivity).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('postActivity complete!')
        );
    }

    putActivity(id: number) {
        this.calls.PutActivity(this.ClientActivity).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('putActivity complete!')
        );
        this.data.setID(0);
    }

    onSelect() {
        this.router.navigate(['/activity']);
    }
}