import { Component, OnInit }            from '@angular/core';
import { Router, ActivatedRoute }       from '@angular/router';

import { SearchCategoryComponent }   from './search/search.component';

import { CallCategoryServices }      from './calls/calls.service';
import { DataService }                  from '../../data/data.service';

import { CategoryClass }             from './class/category.class';

@Component({
    templateUrl: './app/inventory/category/category.component.html',
    providers: [CallCategoryServices],
    directives: [SearchCategoryComponent]
})

export class CategoryComponent implements OnInit {
    private ServerCategorys: CategoryClass[] = [
        { CategoryId: 0, CategoryName: 'N/D', CategoryNote: 'N/D' }
    ];
    private ClientCategory: CategoryClass;

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private calls: CallCategoryServices,
        private data: DataService) {
    }

    ngOnInit() {
        this.getAllCategory();
    }

    private getAllCategory(): void {
        this.calls.GetAllCategory().subscribe(
            (data) => {
                this.ServerCategorys = data.json();
            },
            error => console.log(error),
            () => console.log('getAllCategory complete!')
        );
    }

    goToAdd() {
        this.router.navigate(['/inventory/category/add']);
    }

    goToView(category: CategoryClass) {
        this.router.navigate(['/inventory/category/view', category.CategoryId]);
    }
}