import { Component, OnInit, OnDestroy }     from '@angular/core';
import { Router, ActivatedRoute }           from '@angular/router';

import { DataService }                      from '../../../data/data.service';
import { CallInventoryServices }            from '../calls/calls.service';

import { ManufacturerClass }                from '../class/manufacturer.class';

@Component({
    templateUrl: './app/inventory/manufacturer/add-edit/add-edit.component.html',
    providers: [CallInventoryServices]
})

export class AddEditComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerManufacturer: ManufacturerClass = {
        Id: 0,
        Name: "N/D",
        WebSite: "N/D",
    };
    private ClientManufacturer: ManufacturerClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallInventoryServices,
        private data: DataService) { 
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id']; // (+) converts string 'id' to a number
            this.getSingleManufacturer(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleManufacturer(id: number) {
        this.calls.GetSingleManufacturer(id).subscribe(
            (data) => {
                this.ServerManufacturer = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleManufacturer complete!')
        );
    }

    private postManufacturer() {
        this.calls.PostManufacturer(this.ClientManufacturer).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('postManufacturer complete!')
        );
    }

    private putManufacturer(comp: ManufacturerClass) {
        this.calls.PutManufacturer(comp).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('putManufacturer complete!')
        );
    }

    goToManufacturer() {
        this.router.navigate(['/inventory/manufacturer']);
    }

    goToView(comp: ManufacturerClass) {
        this.router.navigate(['/inventory/manufacturer/view', comp.Id]);
    }
}