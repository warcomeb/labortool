import { Component, OnInit }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { SearchManufacturerComponent } from './search/search.component';

import { CallInventoryServices }    from './calls/calls.service';
import { DataService }              from '../../data/data.service';

import { ManufacturerClass }           from './class/manufacturer.class';

@Component({
    templateUrl: './app/inventory/manufacturer/manufacturer.component.html',
    providers: [CallInventoryServices],
    directives: [SearchManufacturerComponent]
})

export class ManufacturerComponent implements OnInit {
    private ServerManufacturers: ManufacturerClass[] = [
        { Id: 0, Name: "N/D", WebSite: "N/D" }
    ];
    private ClientManufacturer: ManufacturerClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallInventoryServices,
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
    } // fine getAllComponent

    goToAdd() {
        this.router.navigate(['/inventory/manufacturer/add']);
    }

    goToEdit() {
        this.router.navigate(['/inventory/manufacturer/edit']);
    }

    goToView(comp: ManufacturerClass) {
        this.router.navigate(['/inventory/manufacturer/view', comp.Id]);
    }
}