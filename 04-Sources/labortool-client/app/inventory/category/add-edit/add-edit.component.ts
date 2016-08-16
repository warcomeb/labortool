import { Component, OnInit, OnDestroy }     from '@angular/core';
import { Router, ActivatedRoute }           from '@angular/router';

import { DataService }                      from '../../../data/data.service';
import { CallCategoryServices }          from '../calls/calls.service';

import { CategoryClass }                 from '../class/category.class';

@Component({
    templateUrl: './app/inventory/category/add-edit/add-edit.component.html',
    providers: [CallCategoryServices]
})

export class AddEditComponent implements OnInit, OnDestroy {
    private sub: any;
    private ServerCategory: CategoryClass = {
        Id: 0,
        Name: "N/D",
        Note: "N/D",
    };
    private ClientCategory: CategoryClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallCategoryServices,
        private data: DataService) { 
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

    private postCategory() {
        this.calls.PostCategory(this.ClientCategory).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('postCategory complete!')
        );
    }

    private putCategory(Category: CategoryClass) {
        this.calls.PutCategory(Category).subscribe(
            data => console.log(data),
            error => console.log(error),
            () => console.log('putCategory complete!')
        );
    }

    goToCategory() {
        this.router.navigate(['/inventory/category']);
    }

    goToView(Category: CategoryClass) {
        this.router.navigate(['/inventory/category/view', Category.Id]);
    }
}