import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { LocationClass } from '../class/location.class';

@Injectable()
export class CallLocationServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllLocation = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/location');
    }

    public GetSingleLocation = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/location/' + id);
    }

    public PostLocation = (item: LocationClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/inventory/location', toAdd, { headers: this.headers });
    }

    public PutLocation = (item: LocationClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/location', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteLocation = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/location/' + id);
    }

}