import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { CatParamTypeClass } from '../class/cat-param-type.class';

@Injectable()
export class CallCatParamTypeServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllCatParamType = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/cat-param-type');
    }

    public GetSingleCatParamType = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/cat-param-type/' + id);
    }
}