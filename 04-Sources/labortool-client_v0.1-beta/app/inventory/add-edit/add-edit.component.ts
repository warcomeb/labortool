import { Component, OnInit }                from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../data/data.service';
import { CallInventoryServices }    from '../calls/calls.service';

import { InventoryClass }           from '../class/inventory.class';

@Component({
    templateUrl: './app/inventory/add-edit/add-edit.component.html',
    providers: [CallInventoryServices]
})

export class AddEditComponent implements OnInit {
    private ID: number = 0;
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
    private ClientComponent: InventoryClass = {
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
        private calls: CallInventoryServices,
        private data: DataService) { 
            this.ID = data.getID();
        }

    ngOnInit() {
        if (this.ID > 0) {
            this.getSingleComponent(this.ID);
        }

    }

    getSingleComponent(id: number) {
        this.calls.GetSingleComponent(id).subscribe(
            (data) => {
                this.ServerComponent = data.json();
            },
            error => console.log(error),
            () => console.log(this.ID)
        );
    }

    postComponent() {
        this.calls.PostComponent(this.ClientComponent).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('postComponent complete!')
        );
    }

    putComponent(id: number) {
        this.calls.PutComponent(this.ClientComponent).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('putComponent complete!')
        );
        this.data.setID(0);
    }

    onSelect() {
        this.router.navigate(['/inventory']);
    }
}