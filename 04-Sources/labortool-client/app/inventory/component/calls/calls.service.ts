import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { ComponentClass } from '../class/component.class';

@Injectable()
export class CallComponentServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    /* Component */
    public GetAllComponent= (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/component');
    }

    public GetSingleComponent = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/component/' + id);
    }

    public PostComponent = (item: ComponentClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/inventory/component', toAdd, { headers: this.headers });
    }

    public PutComponent = (item: ComponentClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/component', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteComponent = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/component' + id);
    }
}