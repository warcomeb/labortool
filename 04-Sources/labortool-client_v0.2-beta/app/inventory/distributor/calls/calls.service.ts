import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { DistributorClass } from '../class/distributor.class';

@Injectable()
export class CallDistributorServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllDistributor = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/distributor');
    }

    public GetSingleDistributor = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/distributor/' + id);
    }

    public PostDistributor = (item: DistributorClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/inventory/distributor', toAdd, { headers: this.headers });
    }

    public PutDistributor = (item: DistributorClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/distributor', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteDistributor = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/distributor/' + id);
    }

}