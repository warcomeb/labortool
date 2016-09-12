import { Component, OnInit }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { SearchManufacturerComponent } from './search/search.component';

import { CallManufacturerServices }    from './calls/calls.service';
import { DataService }              from '../../data/data.service';

import { ManufacturerClass }           from './class/manufacturer.class';

@Component({
    templateUrl: './app/inventory/manufacturer/manufacturer.component.html',
    providers: [CallManufacturerServices],
    directives: [SearchManufacturerComponent]
})

export class ManufacturerComponent implements OnInit {
    private ServerManufacturers: ManufacturerClass[] = [
        { ManufacturerId: 0, ManufacturerName: 'N/D', ManufacturerWebSite: 'N/D' }
    ];

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallManufacturerServices,
        private data: DataService) {
    }

    ngOnInit() {
        this.getAllManufacturer();
    }

    private getAllManufacturer(): void {
        this.calls.GetAllManufacturer().subscribe(
            (data) => {
                this.ServerManufacturers = data.json();
            },
            error => console.log(error),
            () => console.log('getAllManufacturer complete!')
        );
    }

    private goToAdd() {
        this.router.navigate(['/inventory/manufacturer/add']);
    }

    private goToView(comp: ManufacturerClass) {
        this.router.navigate(['/inventory/manufacturer/view', comp.ManufacturerId]);
    }
}