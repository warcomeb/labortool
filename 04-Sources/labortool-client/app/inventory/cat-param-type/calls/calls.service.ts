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
        return this.http.get(this.URL + '/inventory/catparamtype');
    }

    public GetSingleCatParamType = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/catparamtype/' + id);
    }

    public PostCatParamType = (item: CatParamTypeClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/inventory/catparamtype', toAdd, { headers: this.headers });
    }

    public PutCatParamType = (item: CatParamTypeClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/catparamtype', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteCatParamType = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/catparamtype/' + id);
    }

}