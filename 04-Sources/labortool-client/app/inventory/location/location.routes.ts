import { RouterConfig }             from '@angular/router';
import { LocationComponent }    from './location.component';
import { AddEditComponent }         from './add-edit/add-edit.component';
import { ViewComponent }            from './view/view.component';

export const locationRoutes: RouterConfig = [
  { path: 'inventory/location',  component: LocationComponent },
  { path: 'inventory/location/add',  component: AddEditComponent },
  { path: 'inventory/location/edit/:id',  component: AddEditComponent },
  { path: 'inventory/location/view/:id', component: ViewComponent }
];
