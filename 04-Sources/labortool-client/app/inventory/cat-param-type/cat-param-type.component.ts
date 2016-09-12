import { Component, OnInit }            from '@angular/core';
import { Router, ActivatedRoute }       from '@angular/router';

import { SearchCatParamTypeComponent }   from './search/search.component';

import { CallCatParamTypeServices }      from './calls/calls.service';
import { DataService }                  from '../../data/data.service';

import { JoinCatParamTypeClass }             from './class/cat-param-type.class';

@Component({
    templateUrl: './app/inventory/cat-param-type/cat-param-type.component.html',
    providers: [CallCatParamTypeServices],
    directives: [SearchCatParamTypeComponent]
})

export class CatParamTypeComponent implements OnInit {
    private ServerCategoryParamTypers: JoinCatParamTypeClass[] = [
        { CategoryParamTypeId: 0, CategoryParamTypeName: 'N/D', CategoryId: 0, CategoryName: 'N/D', UnitId:0, UnitName: 'N/D', CategoryParamTypeOrder: 'N/D' }
    ];

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
                this.ServerCategoryParamTypers = data.json();
            },
            error => console.log(error),
            () => console.log('getAllCatParamType complete!')
        );
    }

    goToView(catParamType: JoinCatParamTypeClass) {
        this.router.navigate(['/inventory/category_parameter_type/view', catParamType.CategoryParamTypeId]);
    }
}