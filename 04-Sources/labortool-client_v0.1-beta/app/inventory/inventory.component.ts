import { Component, OnInit }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { SearchInventoryComponent } from './search/search.component';

import { CallInventoryServices }    from './calls/calls.service';
import { DataService }              from '../data/data.service';

import { InventoryClass }           from './class/inventory.class';

@Component({
    templateUrl: './app/inventory/inventory.component.html',
    styleUrls: ['./app/inventory/inventory.component.css'],
    providers: [CallInventoryServices],
    directives: [SearchInventoryComponent]
})

export class InventoryComponent implements OnInit {
    private ID: number;
    private ServerComponents: InventoryClass[] = [
        { Id: 0, Name: "N/D", ManufacturerName: "N/D", ManufacturerWebSite: "N/D", PartNumber: 0, DistributorName: "N/D", DistributorWebSite: "N/D", DistributorCode: "N/D", Price: 0, Code: "N/D", LocationPosition: "N/D", LocationContainer: "N/D", LocationSubContainer: "N/D", Datasheet: "N/D", FootprintName: "N/D", FootprintLink: "N/D", CategoryName: "N/D", CategoryNote: "N/D", Note: "N/D" }
    ];
    private ClientComponent: InventoryClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallInventoryServices,
        private data: DataService) {
        this.ID = data.getID();
    }

    ngOnInit() {
        this.getAllComponent();
    }

    private saveID(ID: number) {
        return this.data.setID(ID);
    }

    private deleteComponent(ID: number) {
        this.calls.DeleteComponent(ID).subscribe(
            error => console.log(error),
            () => console.log('DeleteComponent complete')
        );
    } // fine deleteComponent

    private getAllComponent(): void {
        this.calls.GetAllComponent().subscribe(
            (data) => {
                this.ServerComponents = data.json();
            },
            error => console.log(error),
            () => console.log('getAllComponent complete!')
        );
    } // fine getAllComponent

    onSelect() {
        this.router.navigate(['/inventory/add']);
    }
}