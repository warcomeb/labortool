import { RouterConfig }             from '@angular/router';
import { LocationComponent }        from './location.component';
import { AddComponent }             from './add/add.component';
import { EditComponent }            from './edit/edit.component';
import { ViewComponent }            from './view/view.component';

export const locationRoutes: RouterConfig = [
  { path: 'inventory/location',  component: LocationComponent },
  { path: 'inventory/location/add',  component: AddComponent },
  { path: 'inventory/location/edit/:id',  component: EditComponent },
  { path: 'inventory/location/view/:id', component: ViewComponent }
];
