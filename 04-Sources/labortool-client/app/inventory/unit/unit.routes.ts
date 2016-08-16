import { RouterConfig }             from '@angular/router';
import { UnitComponent }       from './unit.component';
import { ViewComponent }            from './view/view.component';

export const unitRoutes: RouterConfig = [
  { path: 'inventory/unit',  component: UnitComponent },
  { path: 'inventory/unit/view/:id', component: ViewComponent }
];
