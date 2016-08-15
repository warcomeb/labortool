import { RouterConfig }             from '@angular/router';
import { ManufacturerComponent }    from './manufacturer.component';
import { AddEditComponent }         from './add-edit/add-edit.component';
import { ViewComponent }            from './view/view.component';

export const manufacturerRoutes: RouterConfig = [
  { path: 'inventory/manufacturer',  component: ManufacturerComponent },
  { path: 'inventory/manufacturer/add',  component: AddEditComponent },
  { path: 'inventory/manufacturer/edit/:id',  component: AddEditComponent },
  { path: 'inventory/manufacturer/view/:id', component: ViewComponent }
];
