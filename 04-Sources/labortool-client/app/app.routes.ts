import {provideRouter, RouterConfig} from '@angular/router';
import {ActivityComponent} from './activity/activity.component';
import {HomeComponent} from './home/home.component';
import {ProductionComponent} from './production/production.component';
import {ProjectComponent} from './project/project.component';
import {InventoryComponent} from './inventory/inventory.component';
import {AboutComponent} from './about/about.component';

const routes: RouterConfig = [
    {
        path: '',
        component: HomeComponent
    },
    {
        path: 'activity',
        component: ActivityComponent
    },
    {
        path: 'production',
        component: ProductionComponent
    },
    {
        path: 'project',
        component: ProjectComponent
    },
    {
        path: 'inventory',
        component: InventoryComponent
    },
    {
        path: 'about',
        component: AboutComponent
    }
];

export const AppRouterProviders = [
    provideRouter(routes)
]