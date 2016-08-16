import { RouterConfig }             from '@angular/router';
import { CategoryComponent }       from './category.component';
import { AddEditComponent }         from './add-edit/add-edit.component';
import { ViewComponent }            from './view/view.component';

export const categoryRoutes: RouterConfig = [
  { path: 'inventory/category',  component: CategoryComponent },
  { path: 'inventory/category/add',  component: AddEditComponent },
  { path: 'inventory/category/edit/:id',  component: AddEditComponent },
  { path: 'inventory/category/view/:id', component: ViewComponent }
];
