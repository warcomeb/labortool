import { Component }                from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

@Component({
    templateUrl: './app/about/about.component.html'
})

export class AboutComponent {
    constructor(
        private route: ActivatedRoute,
        private router: Router) { }
}