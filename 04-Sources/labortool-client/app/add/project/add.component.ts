import {Component} from '@angular/core';
import {NgForm} from '@angular/forms';
import {CallsService} from '../../services/calls.service';
import {ProjClass} from '../../classes/classes';

@Component({
    selector: 'add-proj',
    templateUrl: 'app/add/project/add.component.html',
    styleUrls: ['app/add/add.component.css'],
    providers: [CallsService]
})

export class AddProjComponent {
    private MyProject:ProjClass = {
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

    postProject() {
        this._callsService.PostProject(this.MyProject).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('postProject complete!'));
    }
};
