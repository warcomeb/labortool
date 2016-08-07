import {Component} from '@angular/core';
import {ROUTER_DIRECTIVES, Router} from '@angular/router';

@Component({
    selector: 'add-acti-btn',
    templateUrl: 'app/button/activity/add.button.component.html',
    styleUrls: ['app/button/add.button.component.css'],
    directives: [ROUTER_DIRECTIVES]
})

export class AddActiBtnComponent {
    constructor(private router: Router) {}
};