import {Component} from '@angular/core';
import {ROUTER_DIRECTIVES, Router} from '@angular/router'
import {NgForm} from '@angular/forms';
import {CallsService} from '../../services/calls.service';
import {ActiClass} from '../../classes/classes';

@Component({
    selector: 'add-acti',
    templateUrl: 'app/add/activity/add.component.html',
    styleUrls: ['app/add/add.component.css'],
    providers: [CallsService],
    directives: [ROUTER_DIRECTIVES]
})

export class AddActiComponent {
    private MyActivity:ActiClass = {
        Id:0,
        Title:"",
        Description:"",
        WorkCode:"",
        Deadline:new Date(0, 0, 0),
        Priority:0,
        Status:0,
        Type:0,
        Employee:0,
        Editable:0,
        Notes:""
    };

    constructor(private router: Router, private _callsService: CallsService) {
        
    }

    AddActivity() {
        this._callsService.PostActivity(this.MyActivity).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('AddActivity complete!'));
    }
};
