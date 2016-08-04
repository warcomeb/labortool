    import {bootstrap} from '@angular/platform-browser-dynamic';
    import {HTTP_PROVIDERS, Http, URLSearchParams} from '@angular/http';
    import {HostComponent} from './configs/host.component';

    import {AppComponent} from './app.component';
    import {AppRouterProviders} from './app.routes';
    import {Fake_DataService} from './fake_data/fake_data.service';

    bootstrap(AppComponent, [Fake_DataService, HTTP_PROVIDERS, HostComponent, AppRouterProviders])
    .catch(err => console.error(err));