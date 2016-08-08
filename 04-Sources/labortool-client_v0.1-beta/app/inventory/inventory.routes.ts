import { RouterConfig }         from '@angular/router';
import { InventoryComponent }    from './inventory.component';
import { AddEditComponent }     from './add-edit/add-edit.component';
import { ViewComponent }        from './view/view.component';

export const inventoryRoutes: RouterConfig = [
  { path: 'inventory',  component: InventoryComponent },
  { path: 'inventory/add',  component: AddEditComponent },
  { path: 'inventory/edit/:id',  component: AddEditComponent },
  { path: 'inventory/view/:id', component: ViewComponent }
];
