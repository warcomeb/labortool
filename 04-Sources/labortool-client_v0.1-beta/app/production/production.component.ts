import { Component }                from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

@Component({
    templateUrl: './app/production/production.component.html'
})

export class ProductionComponent {
    constructor(
        private route: ActivatedRoute,
        private router: Router) { }
}