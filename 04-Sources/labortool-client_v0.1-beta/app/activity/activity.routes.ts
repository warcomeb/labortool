import { RouterConfig }         from '@angular/router';
import { ActivityComponent }    from './activity.component';
import { AddEditComponent }     from './add-edit/add-edit.component';
import { ViewComponent }        from './view/view.component';

export const activityRoutes: RouterConfig = [
  { path: 'activity', component: ActivityComponent },
  { path: 'activity/add', component: AddEditComponent },
  { path: 'activity/edit/:id', component: AddEditComponent },
  { path: 'activity/view/:id', component: ViewComponent }
];
