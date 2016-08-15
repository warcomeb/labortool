import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { FootprintClass } from '../class/footprint.class';

@Injectable()
export class CallFootprintServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllFootprint = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/footprint');
    }

    public GetSingleFootprint = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/footprint/' + id);
    }

    public PostFootprint = (item: FootprintClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/inventory/footprint', toAdd, { headers: this.headers });
    }

    public PutFootprint = (item: FootprintClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/footprint', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteFootprint = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/footprint/' + id);
    }

}