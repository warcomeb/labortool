import { Component, OnInit }            from '@angular/core';
import { Router, ActivatedRoute }       from '@angular/router';

import { SearchLocationComponent }      from './search/search.component';

import { CallLocationServices }         from './calls/calls.service';
import { DataService }                  from '../../data/data.service';

import { LocationClass }                from './class/location.class';

@Component({
    templateUrl: './app/inventory/location/location.component.html',
    providers: [CallLocationServices],
    directives: [SearchLocationComponent]
})

export class LocationComponent implements OnInit {
    private ServerData: LocationClass[] = [
        { LocationId: 0, LocationPosition: 'N/D', LocationContainer: 'N/D', LocationSubContainer: 'N/D' }
    ];
    private ClientData: LocationClass;

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
                this.ServerData = data.json();
            },
            error => console.log(error),
            () => console.log('getAllLocation complete!')
        );
    }

    goToAdd() {
        this.router.navigate(['/inventory/location/add']);
    }

    goToView(location: LocationClass) {
        this.router.navigate(['/inventory/location/view', location.LocationId]);
    }
}