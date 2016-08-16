import { RouterConfig }          from '@angular/router';

import { manufacturerRoutes }    from './manufacturer/manufacturer.routes';
import { distributorRoutes }     from './distributor/distributor.routes';
import { locationRoutes }        from './location/location.routes';
import { footprintRoutes }       from './footprint/footprint.routes';
import { categoryRoutes } from './category/category.routes';

export const inventoryRoutes: RouterConfig = [
  ...manufacturerRoutes,
  ...distributorRoutes,
  ...locationRoutes,
  ...footprintRoutes,
  ...categoryRoutes
];
