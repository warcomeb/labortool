import { RouterConfig }             from '@angular/router';
import { CatParamTypeComponent }    from './cat-param-type.component';
import { ViewComponent }            from './view/view.component';

export const catparamtypeRoutes: RouterConfig = [
  { path: 'inventory/category_parameter_type',  component: CatParamTypeComponent },
  { path: 'inventory/category_parameter_type/view/:id', component: ViewComponent }
];
