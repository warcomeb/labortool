import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallInventoryServices }    from '../calls/calls.service';

import { ManufacturerClass }           from '../class/manufacturer.class';

@Component({
    templateUrl: './app/inventory/manufacturer/view/view.component.html',
    styleUrls: ['./app/inventory/manufacturer/view/view.component.css'],
    providers: [CallInventoryServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerManufacturer: ManufacturerClass = {
        Id: 0,
        Name: "N/D",
        WebSite: "N/D"
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private calls: CallInventoryServices) {
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

    private deleteManufacturer(manufacturer: ManufacturerClass) {
        this.calls.DeleteManufacturer(manufacturer.Id).subscribe(
            error => console.log(error),
            () => console.log('deleteManufacturer complete!')
        );
    }

    private goToManufacturer() {
        this.router.navigate(['/inventory/manufacturer']);
    }

    private goToEdit(manufacturer: ManufacturerClass) {
        this.router.navigate(['/inventory/manufacturer/edit', manufacturer.Id]);
    }
}