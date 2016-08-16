import { Component, OnInit }            from '@angular/core';
import { Router, ActivatedRoute }       from '@angular/router';

import { SearchLocationComponent }   from './search/search.component';

import { CallLocationServices }      from './calls/calls.service';
import { DataService }                  from '../../data/data.service';

import { LocationClass }             from './class/location.class';

@Component({
    templateUrl: './app/inventory/location/location.component.html',
    providers: [CallLocationServices],
    directives: [SearchLocationComponent]
})

export class LocationComponent implements OnInit {
    private ServerLocations: LocationClass[] = [
        { Id: 0, Position: "N/D", Container: "N/D", SubContainer: "N/D" }
    ];
    private ClientLocation: LocationClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallLocationServices,
        private data: DataService) {
    }

    ngOnInit() {
        this.getAllLocation();
    }

    private getAllLocation(): void {
        this.calls.GetAllLocation().subscribe(
            (data) => {
                this.ServerLocations = data.json();
            },
            error => console.log(error),
            () => console.log('getAllLocation complete!')
        );
    } // fine getAllComponent

    goToAdd() {
        this.router.navigate(['/inventory/location/add']);
    }

    goToEdit() {
        this.router.navigate(['/inventory/location/edit']);
    }

    goToView(location: LocationClass) {
        this.router.navigate(['/inventory/location/view', location.Id]);
    }
}