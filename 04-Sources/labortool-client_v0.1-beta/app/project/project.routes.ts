import { RouterConfig }         from '@angular/router';
import { ProjectComponent }    from './project.component';
import { AddEditComponent }     from './add-edit/add-edit.component';
import { ViewComponent }        from './view/view.component';

export const projectRoutes: RouterConfig = [
  { path: 'project',  component: ProjectComponent },
  { path: 'project/edit/:id',  component: AddEditComponent },
  { path: 'project/view/:id', component: ViewComponent }
];
