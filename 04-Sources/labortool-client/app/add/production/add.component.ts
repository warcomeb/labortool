import {Component} from '@angular/core';
import {NgForm} from '@angular/forms';
import {CallsService} from '../../services/calls.service';
import {ProdClass} from '../../classes/classes';

@Component({
    selector: 'add-prod',
    templateUrl: 'app/add/production/add.component.html',
    styleUrls: ['app/add/add.component.css'],
    providers: [CallsService]
})

export class AddProdComponent {
    private MyProduction:ProdClass;

    constructor(private _callsService: CallsService) {
        
    }

    postProduction() {
        this._callsService.PostProduction(this.MyProduction).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('AddProduction complete!'));
    }
};
