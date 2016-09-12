import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallComponentServices }    from '../calls/calls.service';
import { CallManufacturerServices } from '../../manufacturer/calls/calls.service';
import { CallDistributorServices } from '../../distributor/calls/calls.service';
import { CallLocationServices } from '../../location/calls/calls.service';
import { CallFootprintServices } from '../../footprint/calls/calls.service';
import { CallCategoryServices } from '../../category/calls/calls.service';
import { CallCatParamTypeServices } from '../../cat-param-type/calls/calls.service';
import { CallUnitServices } from '../../unit/calls/calls.service';
import { CallComponentParamServices } from '../../component-param/calls/calls.service';

import { ComponentClass }                   from '../class/component.class';
import { ManufacturerClass } from '../../manufacturer/class/manufacturer.class';
import { DistributorClass } from '../../distributor/class/distributor.class';
import { LocationClass } from '../../location/class/location.class';
import { FootprintClass } from '../../footprint/class/footprint.class';
import { CategoryClass } from '../../category/class/category.class';
import { CategoryParamTypeClass } from '../../cat-param-type/class/cat-param-type.class';
import { UnitClass } from '../../unit/class/unit.class';
import { ComponentParamClass, ServerPrefix } from '../../component-param/class/component-param.class';

@Component({
    templateUrl: './app/inventory/component/view/view.component.html',
    styleUrls: ['./app/inventory/component/view/view.component.css'],
    providers: [CallComponentServices,
                CallManufacturerServices,
                CallDistributorServices,
                CallLocationServices,
                CallFootprintServices,
                CallCategoryServices,
                CallCatParamTypeServices,
                CallUnitServices,
                CallComponentParamServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerComponent: ComponentClass = {
        ComponentId: 0,
        ComponentName: 'N/D',
        ComponentManufacturer: 0,
        ComponentPartNumber: 'N/D',
        ComponentDistributor: 0,
        ComponentDistributorCode: 'N/D',
        ComponentPrice: 0.00,
        ComponentCode: 'N/D',
        ComponentLocation: 0,
        ComponentDatasheet: 'N/D',
        ComponentFootprint: 0,
        ComponentCategory: 0,
        ComponentNote: 'N/D'
    };
    private ServerManufacturer: ManufacturerClass = {
        ManufacturerId: 0,
        ManufacturerName: 'N/A',
        ManufacturerWebSite: 'N/A'
    };
    private ServerDistributor: DistributorClass = {
        DistributorId: 0,
        DistributorName: 'N/A',
        DistributorWebSite: 'N/A'
    };
    private ServerLocation: LocationClass = {
        LocationId: 0,
        LocationPosition: 'N/A',
        LocationContainer: 'N/A',
        LocationSubContainer: 'N/A'
    };
    private ServerFootprint: FootprintClass = {
        FootprintId: 0,
        FootprintName: 'N/A',
        FootprintLink: 'N/A'
    };
    private ServerCategory: CategoryClass = {
        CategoryId: 0,
        CategoryName: 'N/A',
        CategoryNote: 'N/A'
    };
    private ServerCategoryParamType: CategoryParamTypeClass = {
        CategoryParamTypeId: 0,
        CategoryParamTypeName: 'N/A',
        CategoryParamTypeUnit: 0,
        CategoryParamTypeCategory: 0,
        CategoryParamTypeOrder: 'N/A',
        CategoryParamTypeNote: 'N/A',
        
    };
    private ServerUnit: UnitClass = {
        UnitId: 0,
        UnitName: 'N/A',
        UnitShortName: 'N/A',
        UnitNote: 'N/A'
    };
    private prefix: ServerPrefix;
    private ServerComponentParam: ComponentParamClass = {
        ComponentParamId: 0,
        ComponentParamComponent: 0,
        ComponentParamCategoryParamType: 0,
        ComponentParamValue: 'N/A',
        ComponentParamPrefix: this.prefix,
        ComponentParamNote: 'N/A'
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private compCalls: CallComponentServices,
        private manuCalls: CallManufacturerServices,
        private distCalls: CallDistributorServices,
        private locaCalls: CallLocationServices,
        private footCalls: CallFootprintServices,
        private cateCalls: CallCategoryServices,
        private cptCalls: CallCatParamTypeServices,
        private unitCalls: CallUnitServices,
        private copaCalls: CallComponentParamServices) { 
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id'];
            this.getSingleComponent(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleComponent(id: number) {
        this.compCalls.GetSingleComponent(id).subscribe(
            (data) => {
                this.ServerComponent = data.json();
                this.getSingleManufacturer(this.ServerComponent.ComponentManufacturer);
                this.getSingleDistributor(this.ServerComponent.ComponentDistributor);
                this.getSingleLocation(this.ServerComponent.ComponentLocation);
                this.getSingleFootprint(this.ServerComponent.ComponentFootprint);
                this.getSingleCategory(this.ServerComponent.ComponentCategory);
            },
            error => console.log(error),
            () => console.log('getSingleComponent complete!')
        );
    }

    private getSingleManufacturer(id: number) {
        this.manuCalls.GetSingleManufacturer(id).subscribe(
            (data) => {
                this.ServerManufacturer = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleManufacturer complete!')
        );
    }

    private getSingleDistributor(id: number) {
        this.distCalls.GetSingleDistributor(id).subscribe(
            (data) => {
                this.ServerDistributor = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleDistributor complete!')
        );
    }

    private getSingleLocation(id: number) {
        this.locaCalls.GetSingleLocation(id).subscribe(
            (data) => {
                this.ServerLocation = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleLocation complete!')
        );
    }

    private getSingleFootprint(id: number) {
        this.footCalls.GetSingleFootprint(id).subscribe(
            (data) => {
                this.ServerFootprint = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleFootprint complete!')
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

    private getSingleCategoryParamType(id: number) {
        this.cptCalls.GetSingleCatParamType(id).subscribe(
            (data) => {
                this.ServerCategoryParamType = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleCategoryParamType complete!')
        );
    }

    private getSingleUnit(id: number) {
        this.unitCalls.GetSingleUnit(id).subscribe(
            (data) => {
                this.ServerUnit = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleCategory complete!')
        );
    }

    private getSingleComponentParam(id: number) {
        this.copaCalls.GetSingleComponentParam(id).subscribe(
            (data) => {
                this.ServerComponentParam = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleComponentParam complete!')
        );
    }

    private deleteComponent(comp: ComponentClass) {
        this.compCalls.DeleteComponent(comp.ComponentId).subscribe(
            error => console.log(error),
            () => console.log('deleteComponent complete!')
        );
    }

    private goToComponent() {
        this.router.navigate(['/inventory/component']);
    }

    private goToEdit(comp: ComponentClass) {
        this.router.navigate(['/inventory/component/edit', comp.ComponentId]);
    }
}