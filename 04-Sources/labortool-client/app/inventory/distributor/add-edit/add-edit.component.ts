import { Component, OnInit, OnDestroy }     from '@angular/core';
import { Router, ActivatedRoute }           from '@angular/router';

import { DataService }                      from '../../../data/data.service';
import { CallDistributorServices }          from '../calls/calls.service';

import { DistributorClass }                 from '../class/distributor.class';

@Component({
    templateUrl: './app/inventory/distributor/add-edit/add-edit.component.html',
    providers: [CallDistributorServices]
})

export class AddEditComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerDistributor: DistributorClass = {
        Id: 0,
        Name: "N/D",
        WebSite: "N/D",
    };
    private ClientDistributor: DistributorClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallDistributorServices,
        private data: DataService) { 
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

    private postDistributor() {
        this.calls.PostDistributor(this.ClientDistributor).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('postDistributor complete!')
        );
    }

    private putDistributor(distributor: DistributorClass) {
        this.calls.PutDistributor(distributor).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('putDistributor complete!')
        );
    }

    goToDistributor() {
        this.router.navigate(['/inventory/distributor']);
    }

    goToView(distributor: DistributorClass) {
        this.router.navigate(['/inventory/distributor/view', distributor.Id]);
    }
}