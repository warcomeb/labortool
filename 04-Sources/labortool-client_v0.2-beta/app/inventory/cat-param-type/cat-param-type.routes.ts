import { RouterConfig }             from '@angular/router';
import { CatParamTypeComponent }    from './cat-param-type.component';
import { ViewComponent }            from './view/view.component';

export const categoryRoutes: RouterConfig = [
  { path: 'inventory/category',  component: CatParamTypeComponent },
  { path: 'inventory/category/view/:id', component: ViewComponent }
];
