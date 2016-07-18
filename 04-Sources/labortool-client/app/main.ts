    import {bootstrap} from '@angular/platform-browser-dynamic';
    import {HTTP_PROVIDERS, Http, URLSearchParams} from '@angular/http';
    import {HostComponent} from './configs/host.component';
    import {AppComponent} from './app.component';
    bootstrap(AppComponent, [HTTP_PROVIDERS, HostComponent]);