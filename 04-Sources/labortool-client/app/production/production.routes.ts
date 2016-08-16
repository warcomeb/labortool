import { RouterConfig }         from '@angular/router';
import { ProductionComponent }    from './production.component';
import { AddEditComponent }     from './add-edit/add-edit.component';
import { ViewComponent }        from './view/view.component';

export const productionRoutes: RouterConfig = [
  { path: 'production',  component: ProductionComponent },
  { path: 'production/edit/:id',  component: AddEditComponent },
  { path: 'production/view/:id', component: ViewComponent }
];
