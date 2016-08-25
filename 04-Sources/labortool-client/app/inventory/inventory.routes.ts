import { RouterConfig }          from '@angular/router';

import { manufacturerRoutes }    from './manufacturer/manufacturer.routes';
import { distributorRoutes }     from './distributor/distributor.routes';
import { locationRoutes }        from './location/location.routes';
import { footprintRoutes }       from './footprint/footprint.routes';
import { categoryRoutes } from './category/category.routes';
import { catparamtypeRoutes } from './cat-param-type/cat-param-type.routes';
import { unitRoutes } from './unit/unit.routes'

export const inventoryRoutes: RouterConfig = [
  ...manufacturerRoutes,
  ...distributorRoutes,
  ...locationRoutes,
  ...footprintRoutes,
  ...categoryRoutes,
  ...catparamtypeRoutes,
  ...unitRoutes
];
