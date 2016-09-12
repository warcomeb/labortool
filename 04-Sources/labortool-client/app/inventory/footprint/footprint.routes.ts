import { RouterConfig }             from '@angular/router';
import { FootprintComponent }       from './footprint.component';
import { AddComponent }         from './add/add.component';
import { EditComponent }         from './edit/edit.component';
import { ViewComponent }            from './view/view.component';

export const footprintRoutes: RouterConfig = [
  { path: 'inventory/footprint',  component: FootprintComponent },
  { path: 'inventory/footprint/add',  component: AddComponent },
  { path: 'inventory/footprint/edit/:id',  component: EditComponent },
  { path: 'inventory/footprint/view/:id', component: ViewComponent }
];
