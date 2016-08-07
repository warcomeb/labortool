import {Component, OnInit} from '@angular/core';
import {ROUTER_DIRECTIVES, Router} from '@angular/router';
import {NgForm} from '@angular/forms';
import {CallsService} from '../../services/calls.service';
import {MemoryDataService} from '../../services/memory.data.service';
import {ComponentClass} from '../../classes/classes';

@Component({
    selector: 'add-inve',
    templateUrl: 'app/add/inventory/add.component.html',
    styleUrls: ['app/add/add.component.css'],
    providers: [CallsService],
    directives: [ROUTER_DIRECTIVES]
})

export class AddInveComponent implements OnInit {
    private ID:number = 0;
    private ClientComponent:ComponentClass;
    private ServerComponent:ComponentClass = {
        Id:0,
        Name:"",
        ManufacturerName:"",
        ManufacturerWebSite:"",
        PartNumber:0,
        DistributorName:"",
        DistributorWebSite:"",
        DistributorCode:"",
        Price:0.00,
        Code:"",
        LocationPosition:"",
        LocationContainer:"",
        LocationSubContainer:"",
        Datasheet:"",
        FootprintName:"",
        FootprintLink:"",
        CategoryName:"",
        CategoryNote:"",
        Note:""
    };

    constructor(private router: Router, private _callsService:CallsService, private _memoryDataService:MemoryDataService) {
        this.ID = _memoryDataService.getID();
    }

    ngOnInit() {
        if (this.ID > 0) {
            this.getSingleComponent(this.ID);
        }

    }

    getSingleComponent(id:number) {
        this._callsService.GetSingleComponent(id).subscribe(
            (component) => {
                this.ServerComponent = component.json();
            },
            error => console.log(error),
            () => console.log(this.ID)
        );
    }

    postComponent() {
        this._callsService.PostComponent(this.ClientComponent).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('postComponent complete!')
        );
    }

    putComponent(id:number) {
        this._callsService.PutComponent(this.ClientComponent).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('putComponent complete!')
        );

        this._memoryDataService.setID(0);
    }
};
