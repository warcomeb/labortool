import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallDistributorServices }    from '../calls/calls.service';

import { DistributorClass }           from '../class/distributor.class';

@Component({
    templateUrl: './app/inventory/distributor/view/view.component.html',
    styleUrls: ['./app/inventory/distributor/view/view.component.css'],
    providers: [CallDistributorServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerDistributor: DistributorClass = {
        Id: 0,
        Name: "N/D",
        WebSite: "N/D"
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private calls: CallDistributorServices) {
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id']; // (+) converts string 'id' to a number
            this.getSingleDistributor(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleDistributor(id: number) {
        this.calls.GetSingleDistributor(id).subscribe(
            (data) => {
                this.ServerDistributor = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleDistributor complete!')
        );
    }

    private deleteDistributor(Distributor: DistributorClass) {
        this.calls.DeleteDistributor(Distributor.Id).subscribe(
            error => console.log(error),
            () => console.log('deleteDistributor complete!')
        );
    }

    private goToDistributor() {
        this.router.navigate(['/inventory/distributor']);
    }

    private goToEdit(distributor: DistributorClass) {
        this.router.navigate(['/inventory/distributor/edit', distributor.Id]);
    }
}