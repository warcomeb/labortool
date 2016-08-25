import { Component, OnInit }            from '@angular/core';
import { Router, ActivatedRoute }       from '@angular/router';

import { SearchDistributorComponent }   from './search/search.component';

import { CallDistributorServices }      from './calls/calls.service';
import { DataService }                  from '../../data/data.service';

import { DistributorClass }             from './class/distributor.class';

@Component({
    templateUrl: './app/inventory/distributor/distributor.component.html',
    providers: [CallDistributorServices],
    directives: [SearchDistributorComponent]
})

export class DistributorComponent implements OnInit {
    private ServerDistributors: DistributorClass[] = [
        { Id: 0, Name: "N/D", WebSite: "N/D" }
    ];

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallDistributorServices,
        private data: DataService) {
    }

    ngOnInit() {
        this.getAllDistributor();
    }

    private getAllDistributor(): void {
        this.calls.GetAllDistributor().subscribe(
            (data) => {
                this.ServerDistributors = data.json();
            },
            error => console.log(error),
            () => console.log('getAllDistributor complete!')
        );
    }

    goToAdd() {
        this.router.navigate(['/inventory/distributor/add']);
    }

    goToView(distributor: DistributorClass) {
        this.router.navigate(['/inventory/distributor/view', distributor.Id]);
    }
}