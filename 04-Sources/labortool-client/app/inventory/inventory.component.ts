import {Component, OnInit} from '@angular/core';
import {ROUTER_DIRECTIVES, Router} from '@angular/router';
import {ComponentClass} from '../classes/classes';
import {CallsService} from '../services/calls.service';
import {BreadcrumbsComponent} from '../breadcrumbs/breadcrumbs.component';
import {SearchInveComponent} from '../search/inventory/search.component';
import {AddInveBtnComponent} from '../button/inventory/add.button.component';
import {MemoryDataService} from '../services/memory.data.service';

@Component({
    selector: 'my-inventory',
    templateUrl: 'app/inventory/inventory.component.html',
    styleUrls: ['app/inventory/inventory.component.css'],    
    directives: [ROUTER_DIRECTIVES, BreadcrumbsComponent, SearchInveComponent, AddInveBtnComponent],
    providers: [CallsService]
})

export class InventoryComponent implements OnInit {
    public prova = 100000;

    private ServerComponents:ComponentClass [];
    
    constructor(private router: Router, private _callsService:CallsService, private _memoryDataService:MemoryDataService) {}
    
    ngOnInit() {
        this.getAllComponent();
    }

    private saveID(ID:number) {
        return this._memoryDataService.setID(ID);
    }

    private deleteComponent(ID:number) {
        this._callsService.DeleteComponent(ID).subscribe(
            error => console.log(error),
            () => console.log('DeleteComponent complete')
        );
    } // fine deleteComponent

    private getAllComponent():void {
        this._callsService.GetAllComponent().subscribe(
            (component) => {
                this.ServerComponents = component.json();
            },
            error => console.log(error),
            () => console.log('getAllComponent complete!')
        );
    } // fine getAllComponent
}