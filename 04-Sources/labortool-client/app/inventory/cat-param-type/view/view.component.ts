import { Component,
         OnInit, 
         OnDestroy }                  from '@angular/core';
import { Router,
         ActivatedRoute }             from '@angular/router';
import { DataService }                from '../../../data/data.service';
import { CallCatParamTypeServices }   from '../calls/calls.service';
import { CallCategoryServices } from '../../category/calls/calls.service';
import { CallUnitServices }           from '../../unit/calls/calls.service';

import { CategoryParamTypeClass }          from '../class/cat-param-type.class';
import { CategoryClass }        from '../../category/class/category.class';
import { UnitClass }                  from '../../unit/class/unit.class';


@Component({
    templateUrl: './app/inventory/cat-param-type/view/view.component.html',
    styleUrls: ['./app/inventory/cat-param-type/view/view.component.css'],
    providers: [CallCatParamTypeServices, CallCategoryServices, CallUnitServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerCategoryParamType: CategoryParamTypeClass = {
        CategoryParamTypeId: 0,
        CategoryParamTypeName: 'N/D',
        CategoryParamTypeCategory: 0,
        CategoryParamTypeUnit: 0,
        CategoryParamTypeOrder: 'N/D',
        CategoryParamTypeNote: 'N/D'
    };
    private ServerCategory: CategoryClass = {
        CategoryId: 0,
        CategoryName: 'N/D',
        CategoryNote: 'N/D'
    };
    private ServerUnit: UnitClass = {
        UnitId: 0,
        UnitName: 'N/D',
        UnitShortName: 'N/D',
        UnitNote: 'N/D'
    }

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private cptCalls: CallCatParamTypeServices,
        private unitCalls: CallUnitServices,
        private cateCalls: CallCategoryServices) {
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id']; // (+) converts string 'id' to a number
            this.getSingleCatParamType(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleCatParamType(id: number) {
        this.cptCalls.GetSingleCatParamType(id).subscribe(
            (data) => {
                this.ServerCategoryParamType = data.json();
                this.getSingleCategory(this.ServerCategoryParamType.CategoryParamTypeCategory);
                this.getSingleUnit(this.ServerCategoryParamType.CategoryParamTypeUnit);
            },
            error => console.log(error),
            () => console.log('getSingleCatParamType complete!')
        );
    }

    private getSingleCategory(id: number) {
        this.cateCalls.GetSingleCategory(id).subscribe(
            (data) => {
                this.ServerCategory = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleCategory complete!')
        );
    }

    private getSingleUnit(id: number) {
        this.unitCalls.GetSingleUnit(id).subscribe(
            (data) => {
                this.ServerUnit = data.json();
            },
            error => console.log(error),
                () => console.log('getSingleUnit complete!')
        );
    }

    private goToCatParamType() {
        this.router.navigate(['/inventory/category_parameter_type']);
    }
}