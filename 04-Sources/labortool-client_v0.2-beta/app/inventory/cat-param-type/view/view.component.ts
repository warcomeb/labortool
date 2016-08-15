import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallCatParamTypeServices }    from '../calls/calls.service';

import { CatParamTypeClass }           from '../class/cat-param-type.class';

@Component({
    templateUrl: './app/inventory/cat-param-type/view/view.component.html',
    styleUrls: ['./app/inventory/cat-param-type/view/view.component.css'],
    providers: [CallCatParamTypeServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerCatParamType: CatParamTypeClass = {
        Id: 0,
        Name: "N/D",
        CategoryId: 0,
        UnitId: 0,
        Order: "N/D",
        Note: "N/D"
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private calls: CallCatParamTypeServices) {
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id']; // (+) converts string 'id' to a number
            this.getSingleCatParamType(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleCatParamType(id: number) {
        this.calls.GetSingleCatParamType(id).subscribe(
            (data) => {
                this.ServerCatParamType = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleCatParamType complete!')
        );
    }

    private goToCatParamType() {
        this.router.navigate(['/inventory/cat-param-type']);
    }
}