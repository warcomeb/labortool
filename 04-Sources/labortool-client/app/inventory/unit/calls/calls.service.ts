import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { UnitClass } from '../class/unit.class';

@Injectable()
export class CallUnitServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllUnit = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/unit');
    }

    public GetSingleUnit = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/unit/' + id);
    }

    public PostUnit = (item: UnitClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/inventory/unit', toAdd, { headers: this.headers });
    }

    public PutUnit = (item: UnitClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/unit', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteUnit = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/unit/' + id);
    }

}