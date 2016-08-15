import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallFootprintServices }    from '../calls/calls.service';

import { FootprintClass }           from '../class/footprint.class';

@Component({
    templateUrl: './app/inventory/footprint/view/view.component.html',
    styleUrls: ['./app/inventory/footprint/view/view.component.css'],
    providers: [CallFootprintServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerFootprint: FootprintClass = {
        Id: 0,
        Name: "N/D",
        WebSite: "N/D"
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private calls: CallFootprintServices) {
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

    private deleteFootprint(footprint: FootprintClass) {
        this.calls.DeleteFootprint(footprint.Id).subscribe(
            error => console.log(error),
            () => console.log('deleteFootprint complete!')
        );
    }

    private goToFootprint() {
        this.router.navigate(['/inventory/footprint']);
    }

    private goToEdit(footprint: FootprintClass) {
        this.router.navigate(['/inventory/footprint/edit', footprint.Id]);
    }
}