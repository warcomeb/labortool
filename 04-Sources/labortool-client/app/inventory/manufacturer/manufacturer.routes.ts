import { RouterConfig }             from '@angular/router';
import { ManufacturerComponent }    from './manufacturer.component';
import { AddComponent }             from './add/add.component';
import { EditComponent }            from './edit/edit.component';
import { ViewComponent }            from './view/view.component';

export const manufacturerRoutes: RouterConfig = [
  { path: 'inventory/manufacturer',  component: ManufacturerComponent },
  { path: 'inventory/manufacturer/add',  component: AddComponent },
  { path: 'inventory/manufacturer/edit/:id',  component: EditComponent },
  { path: 'inventory/manufacturer/view/:id', component: ViewComponent }
];
