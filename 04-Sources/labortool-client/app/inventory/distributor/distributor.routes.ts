import { RouterConfig }             from '@angular/router';
import { DistributorComponent }    from './distributor.component';
import { AddEditComponent }         from './add-edit/add-edit.component';
import { ViewComponent }            from './view/view.component';

export const distributorRoutes: RouterConfig = [
  { path: 'inventory/distributor',  component: DistributorComponent },
  { path: 'inventory/distributor/add',  component: AddEditComponent },
  { path: 'inventory/distributor/edit/:id',  component: AddEditComponent },
  { path: 'inventory/distributor/view/:id', component: ViewComponent }
];
