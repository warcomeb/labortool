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
    private ServerData: CategoryClass = {
        CategoryId: 0,
        CategoryName: 'N/D',
        CategoryNote: 'N/D'
    };

    constructor(
        private route: ActivatedRoute,
        private router: Router,
        private data: DataService,
        private calls: CallCategoryServices) {
    }

    ngOnInit() {
        this.sub = this.route.params.subscribe(params => {
            let id = +params['id'];
            this.getSingleCategory(id);
        });
    }

    ngOnDestroy() {
        this.sub.unsubscribe();
    }

    private getSingleCategory(id: number) {
        this.calls.GetSingleCategory(id).subscribe(
            (data) => {
                this.ServerData = data.json();
            },
            error => console.log(error),
            () => console.log('getSingleCategory complete!')
        );
    }

    private deleteCategory(_category: CategoryClass) {
        this.calls.DeleteCategory(_category.CategoryId).subscribe(
            undefined,
            error => console.log(error),
            () => { console.log('deleteCategory complete!');
                    this.goToCategory();
            }
        );
        //setTimeout(() => { this.goToCategory(); }, 1000); 
    }

    private goToCategory() {
        this.router.navigate(['/inventory/category']);
    }

    private goToEdit(category: CategoryClass) {
        this.router.navigate(['/inventory/category/edit', category.CategoryId]);
    }
}