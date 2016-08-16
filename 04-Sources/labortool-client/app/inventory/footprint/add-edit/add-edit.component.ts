import { Component, OnInit, OnDestroy }     from '@angular/core';
import { Router, ActivatedRoute }           from '@angular/router';

import { DataService }                      from '../../../data/data.service';
import { CallFootprintServices }          from '../calls/calls.service';

import { FootprintClass }                 from '../class/footprint.class';

@Component({
    templateUrl: './app/inventory/footprint/add-edit/add-edit.component.html',
    providers: [CallFootprintServices]
})

export class AddEditComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerFootprint: FootprintClass = {
        Id: 0,
        Name: "N/D",
        WebSite: "N/D",
    };
    private ClientFootprint: FootprintClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallFootprintServices,
        private data: DataService) { 
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id']; // (+) converts string 'id' to a number
            this.getSingleFootprint(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleFootprint(id: number) {
        this.calls.GetSingleFootprint(id).subscribe(
            (data) => {
                this.ServerFootprint = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleFootprint complete!')
        );
    }

    private postFootprint() {
        this.calls.PostFootprint(this.ClientFootprint).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('postFootprint complete!')
        );
    }

    private putFootprint(footprint: FootprintClass) {
        this.calls.PutFootprint(footprint).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('putFootprint complete!')
        );
    }

    goToFootprint() {
        this.router.navigate(['/inventory/footprint']);
    }

    goToView(footprint: FootprintClass) {
        this.router.navigate(['/inventory/footprint/view', footprint.Id]);
    }
}