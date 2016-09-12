import { RouterConfig }             from '@angular/router';
import { CategoryComponent }       from './category.component';
import { AddComponent }         from './add/add.component';
import { EditComponent }         from './edit/edit.component';
import { ViewComponent }            from './view/view.component';

export const categoryRoutes: RouterConfig = [
  { path: 'inventory/category',  component: CategoryComponent },
  { path: 'inventory/category/add',  component: AddComponent },
  { path: 'inventory/category/edit/:id',  component: EditComponent },
  { path: 'inventory/category/view/:id', component: ViewComponent }
];
