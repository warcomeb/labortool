import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../connection/connection.service';
import { ProductionClass } from '../class/production.class';

@Injectable()
export class CallProductionServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllProduction = (): Observable<Response> => {
        return this.http.get(this.URL + '/production');
    }

    public GetSingleProduction = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/production' + id);
    }

    public PostProduction = (item: ProductionClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/production', toAdd, { headers: this.headers });
    }

    public PutProduction = (item: ProductionClass): Observable<Response> => {
        return this.http.put(this.URL + '/production', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteProduction = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/production' + id);
    }

}