import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { CategoryClass } from '../class/category.class';

@Injectable()
export class CallCategoryServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllCategory = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/category');
    }

    public GetSingleCategory = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/category/' + id);
    }

    public PostCategory = (item: CategoryClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/inventory/category', toAdd, { headers: this.headers });
    }

    public PutCategory = (item: CategoryClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/category', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteCategory = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/category/' + id);
    }

}