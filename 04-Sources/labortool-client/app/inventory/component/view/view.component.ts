import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallInventoryServices }    from '../calls/calls.service';

import { InventoryClass }           from '../class/component.class';

@Component({
    templateUrl: './app/inventory/component/view/view.component.html',
    styleUrls: ['./app/inventory/component/view/view.component.css'],
    providers: [CallInventoryServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerComponent: InventoryClass = {
        Id: 0,
        Name: "N/D",
        ManufacturerName: "N/D",
        ManufacturerWebSite: "N/D",
        PartNumber: 0,
        DistributorName: "N/D",
        DistributorWebSite: "N/D",
        DistributorCode: "N/D",
        Price: 0.00,
        Code: "N/D",
        LocationPosition: "N/D",
        LocationContainer: "N/D",
        LocationSubContainer: "N/D",
        Datasheet: "N/D",
        FootprintName: "N/D",
        FootprintLink: "N/D",
        CategoryName: "N/D",
        CategoryNote: "N/D",
        Note: "N/D"
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
            this.getSingleComponent(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleComponent(id: number) {
        this.calls.GetSingleComponent(id).subscribe(
            (data) => {
                this.ServerComponent = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleComponent complete!')
        );
    }

    private deleteComponent(comp: InventoryClass) {
        this.calls.DeleteComponent(comp.Id).subscribe(
            error => console.log(error),
            () => console.log('deleteComponent complete!')
        );
    } // fine deleteComponent

    private goToInventory() {
        this.router.navigate(['/inventory/manufacturer']);
    }

    private goToEdit(comp: InventoryClass) {
        this.router.navigate(['/inventory/manufacturer/edit', comp.Id]);
    }
}