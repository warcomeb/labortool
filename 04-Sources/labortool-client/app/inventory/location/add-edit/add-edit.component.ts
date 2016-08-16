import { Component, OnInit, OnDestroy }     from '@angular/core';
import { Router, ActivatedRoute }           from '@angular/router';

import { DataService }                      from '../../../data/data.service';
import { CallLocationServices }          from '../calls/calls.service';

import { LocationClass }                 from '../class/location.class';

@Component({
    templateUrl: './app/inventory/location/add-edit/add-edit.component.html',
    providers: [CallLocationServices]
})

export class AddEditComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerLocation: LocationClass = {
        Id: 0,
        Position: "N/D",
        Container: "N/D",
        SubContainer: "N/D"
    };
    private ClientLocation: LocationClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallLocationServices,
        private data: DataService) { 
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id']; // (+) converts string 'id' to a number
            this.getSingleLocation(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleLocation(id: number) {
        this.calls.GetSingleLocation(id).subscribe(
            (data) => {
                this.ServerLocation = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleLocation complete!')
        );
    }

    private postLocation() {
        this.calls.PostLocation(this.ClientLocation).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('postLocation complete!')
        );
    }

    private putLocation(location: LocationClass) {
        this.calls.PutLocation(location).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('putLocation complete!')
        );
    }

    goToLocation() {
        this.router.navigate(['/inventory/location']);
    }

    goToView(location: LocationClass) {
        this.router.navigate(['/inventory/location/view', location.Id]);
    }
}