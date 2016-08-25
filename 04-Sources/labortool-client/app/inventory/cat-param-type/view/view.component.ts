import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallCatParamTypeServices }    from '../calls/calls.service';
import { CallUnitServices } from '../../unit/calls/calls.service';
import { CallCategoryServices } from '../../category/calls/calls.service';

import { CatParamTypeClass }           from '../class/cat-param-type.class';
import { UnitClass }           from '../../unit/class/unit.class';
import { CategoryClass }           from '../../category/class/category.class';


@Component({
    templateUrl: './app/inventory/cat-param-type/view/view.component.html',
    styleUrls: ['./app/inventory/cat-param-type/view/view.component.css'],
    providers: [CallCatParamTypeServices, CallUnitServices, CallCategoryServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerCatParamType: CatParamTypeClass = {
        Id: 0,
        Name: "N/D",
        CategoryId: 0,
        UnitId: 0,
        Order: "N/D",
        Note: "N/D"
    };
    private ServerUnit: UnitClass = {
        Id: 0,
        Name: '',
        ShortName: '',
        Note: ''
    };
    private ServerCategory: CategoryClass = {
        Id: 0,
        Name: '',
        Note: ''
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private cptCalls: CallCatParamTypeServices,
        private unitCalls: CallUnitServices,
        private categoryCalls: CallCategoryServices) {
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id']; // (+) converts string 'id' to a number
            this.getSingleCatParamType(id);
        });
        this.getSingleUnit(this.ServerCatParamType.UnitId);
        this.getSingleCategory(this.ServerCatParamType.CategoryId);
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleCatParamType(id: number) {
        this.cptCalls.GetSingleCatParamType(id).subscribe(
            (data) => {
                this.ServerCatParamType = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleCatParamType complete!')
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

    private getSingleCategory(id: number) {
        this.categoryCalls.GetSingleCategory(id).subscribe(
            (data) => {
                this.ServerCategory = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleCategory complete!')
        );
    }

    private goToCatParamType() {
        this.router.navigate(['/inventory/category/parameter/type']);
    }
}