import {Component} from '@angular/core';

@Component({
    selector: 'add-btn-prod',
    templateUrl: 'app/button/add.button.component.html',
    styleUrls: ['app/button/add.button.component.css']
})

export class AddBtnProdComponent {
    public nome:string = 'Add new production!';
};