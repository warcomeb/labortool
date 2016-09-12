import { Component, OnInit }            from '@angular/core';
import { Router, ActivatedRoute }       from '@angular/router';

import { SearchFootprintComponent }   from './search/search.component';

import { CallFootprintServices }      from './calls/calls.service';
import { DataService }                  from '../../data/data.service';

import { FootprintClass }             from './class/footprint.class';

@Component({
    templateUrl: './app/inventory/footprint/footprint.component.html',
    providers: [CallFootprintServices],
    directives: [SearchFootprintComponent]
})

export class FootprintComponent implements OnInit {
    private ServerFootprints: FootprintClass[] = [
        { FootprintId: 0, FootprintName: 'N/D', FootprintLink: 'N/D' }
    ];

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallFootprintServices,
        private data: DataService) {
    }

    ngOnInit() {
        this.getAllFootprint();
    }

    private getAllFootprint(): void {
        this.calls.GetAllFootprint().subscribe(
            (data) => {
                this.ServerFootprints = data.json();
            },
            error => console.log(error),
            () => console.log('getAllFootprint complete!')
        );
    }

    goToAdd() {
        this.router.navigate(['/inventory/footprint/add']);
    }

    goToView(footprint: FootprintClass) {
        this.router.navigate(['/inventory/footprint/view', footprint.FootprintId]);
    }
}