    import {bootstrap} from '@angular/platform-browser-dynamic';
    import {HTTP_PROVIDERS, Http, URLSearchParams} from '@angular/http';
    import {HostComponent} from './configs/host.component';
    import {AppComponent} from './app.component';
    import {AppRouterProviders} from './app.routes';
    import {MemoryService} from './services/memory.service';
    bootstrap(AppComponent, [MemoryService, HTTP_PROVIDERS, HostComponent, AppRouterProviders]);