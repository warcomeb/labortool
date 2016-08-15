import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallLocationServices }    from '../calls/calls.service';

import { LocationClass }           from '../class/location.class';

@Component({
    templateUrl: './app/inventory/location/view/view.component.html',
    styleUrls: ['./app/inventory/location/view/view.component.css'],
    providers: [CallLocationServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerLocation: LocationClass = {
        Id: 0,
        Position: "N/D",
        Container: "N/D",
        SubContainer: "N/D"
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private calls: CallLocationServices) {
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

    private deleteLocation(location: LocationClass) {
        this.calls.DeleteLocation(location.Id).subscribe(
            error => console.log(error),
            () => console.log('deleteLocation complete!')
        );
    }

    private goToLocation() {
        this.router.navigate(['/inventory/location']);
    }

    private goToEdit(location: LocationClass) {
        this.router.navigate(['/inventory/location/edit', location.Id]);
    }
}