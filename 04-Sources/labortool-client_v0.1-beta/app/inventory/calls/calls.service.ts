import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../connection/connection.service';
import { InventoryClass } from '../class/inventory.class';

@Injectable()
export class CallInventoryServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllComponent= (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory');
    }

    public GetSingleComponent= (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory' + id);
    }

    public PostComponent= (item: InventoryClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/inventory', toAdd, { headers: this.headers });
    }

    public PutComponent= (item: InventoryClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteComponent= (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory' + id);
    }

}