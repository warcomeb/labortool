import { Injectable } from '@angular/core';
import { Http, Response, Headers, RequestOptions } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';

@Injectable()
export class CallUnitServices {
    private URL: string;
    private headers: Headers;
    private options: RequestOptions;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');

        this.options = new RequestOptions({ headers: this.headers });
    }

    public GetAllUnit = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/unit');
    }

    public GetSingleUnit = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/unit/' + id);
    }
}