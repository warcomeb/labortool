import { RouterConfig }             from '@angular/router';
import { FootprintComponent }       from './footprint.component';
import { AddEditComponent }         from './add-edit/add-edit.component';
import { ViewComponent }            from './view/view.component';

export const footprintRoutes: RouterConfig = [
  { path: 'inventory/footprint',  component: FootprintComponent },
  { path: 'inventory/footprint/add',  component: AddEditComponent },
  { path: 'inventory/footprint/edit/:id',  component: AddEditComponent },
  { path: 'inventory/footprint/view/:id', component: ViewComponent }
];
