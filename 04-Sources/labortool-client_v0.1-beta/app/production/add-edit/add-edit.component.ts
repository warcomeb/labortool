import { Component }                from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

@Component({
    templateUrl: './app/production/add-edit/add-edit.component.html'
})

export class AddEditComponent {
    constructor(
        private route: ActivatedRoute,
        private router: Router) { }
}