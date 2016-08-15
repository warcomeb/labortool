import { Component, OnInit, OnDestroy }        from '@angular/core';
import { Router, ActivatedRoute }   from '@angular/router';

import { DataService }              from '../../../data/data.service';
import { CallCategoryServices }    from '../calls/calls.service';

import { CategoryClass }           from '../class/category.class';

@Component({
    templateUrl: './app/inventory/category/view/view.component.html',
    styleUrls: ['./app/inventory/category/view/view.component.css'],
    providers: [CallCategoryServices]
})

export class ViewComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerCategory: CategoryClass = {
        Id: 0,
        Name: "N/D",
        Note: "N/D"
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private calls: CallCategoryServices) {
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id']; // (+) converts string 'id' to a number
            this.getSingleCategory(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleCategory(id: number) {
        this.calls.GetSingleCategory(id).subscribe(
            (data) => {
                this.ServerCategory = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleCategory complete!')
        );
    }

    private deleteCategory(category: CategoryClass) {
        this.calls.DeleteCategory(category.Id).subscribe(
            error => console.log(error),
            () => console.log('deleteCategory complete!')
        );
    }

    private goToCategory() {
        this.router.navigate(['/inventory/category']);
    }

    private goToEdit(category: CategoryClass) {
        this.router.navigate(['/inventory/category/edit', category.Id]);
    }
}