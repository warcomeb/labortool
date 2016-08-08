import { Component }                from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

@Component({
    templateUrl: './app/project/project.component.html'
})

export class ProjectComponent {
    constructor(
        private route: ActivatedRoute,
        private router: Router) { }
}