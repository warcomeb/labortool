import { Component, OnInit }            from '@angular/core';
import { Router, ActivatedRoute }       from '@angular/router';

import { SearchUnitComponent }   from './search/search.component';

import { CallUnitServices }      from './calls/calls.service';
import { DataService }                  from '../../data/data.service';

import { UnitClass }             from './class/unit.class';

@Component({
    templateUrl: './app/inventory/unit/unit.component.html',
    providers: [CallUnitServices],
    directives: [SearchUnitComponent]
})

export class UnitComponent implements OnInit {
    private ServerUnits: UnitClass[] = [
        { Id: 0, Name: "N/D", ShortName: "N/D", Note: "N/D" }
    ];

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallUnitServices,
        private data: DataService) {
    }

    ngOnInit() {
        this.getAllUnit();
    }

    private getAllUnit(): void {
        this.calls.GetAllUnit().subscribe(
            (data) => {
                this.ServerUnits = data.json();
            },
            error => console.log(error),
            () => console.log('getAllUnit complete!')
        );
    }

    goToView(unit: UnitClass) {
        this.router.navigate(['/inventory/unit/view', unit.Id]);
    }
}