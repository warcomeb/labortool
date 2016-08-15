import { Component, OnInit }            from '@angular/core';
import { Router, ActivatedRoute }       from '@angular/router';

import { SearchCatParamTypeComponent }   from './search/search.component';

import { CallCatParamTypeServices }      from './calls/calls.service';
import { DataService }                  from '../../data/data.service';

import { CatParamTypeClass }             from './class/cat-param-type.class';

@Component({
    templateUrl: './app/inventory/cat-param-type/cat-param-type.component.html',
    providers: [CallCatParamTypeServices],
    directives: [SearchCatParamTypeComponent]
})

export class CatParamTypeComponent implements OnInit {
    private ServerCatParamTypes: CatParamTypeClass[] = [
        { Id: 0, Name: "N/D", CategoryId: 0, UnitId: 0, Order: "N/D", Note: "N/D" }
    ];
    private ClientCatParamType: CatParamTypeClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallCatParamTypeServices,
        private data: DataService) {
    }

    ngOnInit() {
        this.getAllCatParamType();
    }

    private getAllCatParamType(): void {
        this.calls.GetAllCatParamType().subscribe(
            (data) => {
                this.ServerCatParamTypes = data.json();
            },
            error => console.log(error),
            () => console.log('getAllCatParamType complete!')
        );
    } // fine getAllComponent

    goToView(catParamType: CatParamTypeClass) {
        this.router.navigate(['/inventory/cat-param-type/view', catParamType.Id]);
    }
}