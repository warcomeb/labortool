import { provideRouter, RouterConfig }  from '@angular/router';

import { aboutRoutes }        from './about/about.routes';
import { activityRoutes }     from './activity/activity.routes';
import { homeRoutes }         from './home/home.routes';
import { inventoryRoutes }    from './inventory/inventory.routes';
import { productionRoutes }   from './production/production.routes';
import { projectRoutes }      from './project/project.routes';

import { dataProvider }       from './data/data.routes';
import { connectionProvider } from './connection/connection.route'

export const routes: RouterConfig = [
  ...aboutRoutes,
  ...activityRoutes,
  ...homeRoutes,
  ...inventoryRoutes,
  ...productionRoutes,
  ...projectRoutes
];

export const appRouterProviders = [
  provideRouter(routes),
  dataProvider,
  connectionProvider
];

