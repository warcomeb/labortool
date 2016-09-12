import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallManufacturerServices }    from '../calls/calls.service';

import { ManufacturerClass }           from '../class/manufacturer.class';

@Component({
    templateUrl: './app/inventory/manufacturer/view/view.component.html',
    styleUrls: ['./app/inventory/manufacturer/view/view.component.css'],
    providers: [CallManufacturerServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerData: ManufacturerClass = {
        ManufacturerId: 0,
        ManufacturerName: 'N/D',
        ManufacturerWebSite: 'N/D'
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private calls: CallManufacturerServices) {
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id'];
            this.getSingleManufacturer(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleManufacturer(id: number) {
        this.calls.GetSingleManufacturer(id).subscribe(
            (data) => {
                this.ServerData = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleManufacturer complete!')
        );
    }

    private deleteManufacturer(_manufacturer: ManufacturerClass) {
        this.calls.DeleteManufacturer(_manufacturer.ManufacturerId).subscribe(
            undefined,
            error => console.log(error),
            () => { console.log('deleteManufacturer complete!');
                    this.goToManufacturer();
            }
        );
        //setTimeout(() => { this.goToManufacturer(); }, 1000); 
    }

    private goToManufacturer() {
        this.router.navigate(['/inventory/manufacturer']);
    }

    private goToEdit(manufacturer: ManufacturerClass) {
        this.router.navigate(['/inventory/manufacturer/edit', manufacturer.ManufacturerId]);
    }
}