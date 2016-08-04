import {Component} from '@angular/core';

@Component({
    selector: 'add-btn-proj',
    templateUrl: 'app/button/add.button.component.html',
    styleUrls: ['app/button/add.button.component.css']
})

export class AddBtnProjComponent {
    public nome:string = 'Add new project!';
};