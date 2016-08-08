import { Component }                from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

@Component({
    templateUrl: './app/home/home.component.html'
})

export class HomeComponent {
    constructor(
        private route: ActivatedRoute,
        private router: Router) { }
}