import { RouterConfig }             from '@angular/router';
import { CatParamTypeComponent }    from './cat-param-type.component';
import { ViewComponent }            from './view/view.component';

export const catparamtypeRoutes: RouterConfig = [
  { path: 'inventory/category/parameter/type',  component: CatParamTypeComponent },
  { path: 'inventory/category/parameter/type/view/:id', component: ViewComponent }
];
