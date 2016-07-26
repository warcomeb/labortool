import {Component} from '@angular/core';
import {NgForm}    from '@angular/forms';
import {CallsService} from '../../services/calls.service';
import {ClassActivity} from '../../classes/activity.class';


@Component({
    selector: 'my-add-component',
    templateUrl: 'app/add/activity/add.activity.component.html',
    styleUrls: ['app/add/activity/add.activity.component.css'],
    providers: [CallsService]
})

export class AddActivityComponent {
    private MyActivity:ClassActivity = {
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

    constructor(private _callsService: CallsService) {
        
    }

    AddActivity() {
        this._callsService.PostAnActivity(this.MyActivity).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('AddActivity complete!'));
    }


}