import {Component} from '@angular/core';
import {ROUTER_DIRECTIVES, Router} from '@angular/router';

@Component({
    selector: 'add-inve-btn',
    templateUrl: 'app/button/inventory/add.button.component.html',
    styleUrls: ['app/button/add.button.component.css'],
    directives: [ROUTER_DIRECTIVES]
})

export class AddInveBtnComponent {
    constructor(private router: Router) {}
};