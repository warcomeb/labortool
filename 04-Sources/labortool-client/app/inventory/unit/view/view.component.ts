import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallUnitServices }    from '../calls/calls.service';

import { UnitClass }           from '../class/unit.class';

@Component({
    templateUrl: './app/inventory/unit/view/view.component.html',
    styleUrls: ['./app/inventory/unit/view/view.component.css'],
    providers: [CallUnitServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerData: UnitClass = {
        UnitId: 0,
        UnitName: 'N/D',
        UnitShortName: 'N/D',
        UnitNote: 'N/D'
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private calls: CallUnitServices) {
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id'];
            this.getSingleUnit(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleUnit(id: number) {
        this.calls.GetSingleUnit(id).subscribe(
            (data) => {
                this.ServerData = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleUnit complete!')
        );
    }

    private goToUnit() {
        this.router.navigate(['/inventory/unit']);
    }
}