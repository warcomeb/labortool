    import {bootstrap} from '@angular/platform-browser-dynamic';
    
    import {HTTP_PROVIDERS, Http, URLSearchParams} from '@angular/http';
    import {HostComponent} from './configs/host.component';

    import {AppComponent} from './app.component';
    import {appRouterProviders} from './app.routes';
    import {MemoryDataService} from './services/memory.data.service';

    bootstrap(AppComponent, [appRouterProviders, MemoryDataService, HTTP_PROVIDERS, HostComponent])
    .catch(err => console.error(err));