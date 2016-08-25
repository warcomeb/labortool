import { RouterConfig }             from '@angular/router';
import { DistributorComponent }     from './distributor.component';
import { AddComponent }             from './add/add.component';
import { EditComponent }            from './edit/edit.component';
import { ViewComponent }            from './view/view.component';

export const distributorRoutes: RouterConfig = [
  { path: 'inventory/distributor',  component: DistributorComponent },
  { path: 'inventory/distributor/add',  component: AddComponent },
  { path: 'inventory/distributor/edit/:id',  component: EditComponent },
  { path: 'inventory/distributor/view/:id', component: ViewComponent }
];
