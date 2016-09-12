import { Injectable } from '@angular/core';
import { Http, Response, Headers, RequestOptions } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { CategoryClass } from '../class/category.class';

@Injectable()
export class CallCategoryServices {
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

    public GetAllCategory = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/category')
        .catch(this.handleError);
    }

    public GetSingleCategory = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/category/' + id)
        .catch(this.handleError);
    }

    public PostCategory = (body: CategoryClass): Observable<Response> => {
        return this.http.post(this.URL + '/inventory/category', JSON.stringify(body), this.options)
        .catch(this.handleError);
    }

    public PutCategory = (id: number, body: CategoryClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/category/' + id, JSON.stringify(body), this.options)
        .catch(this.handleError);
    }

    public DeleteCategory = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/category/' + id)
        .catch(this.handleError);
    }


    public JoinCategoryParamType = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/category/join/category-param-type/' + id);
    }
    
    private handleError(error: Response) {
        console.error(error);
        return Observable.throw(error.json().error || 'Server error');
    }
}