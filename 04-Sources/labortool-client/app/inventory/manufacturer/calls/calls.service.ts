import { Injectable } from '@angular/core';
import { Http, Response, Headers, RequestOptions } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { ManufacturerClass } from '../class/manufacturer.class';

@Injectable()
export class CallManufacturerServices {
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

    public GetAllManufacturer = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/manufacturer')
        .catch(this.handleError);
    }

    public GetSingleManufacturer = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/manufacturer/' + id)
        .catch(this.handleError);
    }

    public PostManufacturer = (body: ManufacturerClass): Observable<Response> => {
        return this.http.post(this.URL + '/inventory/manufacturer', JSON.stringify(body), this.options)
        .catch(this.handleError);
    }

    public PutManufacturer = (id: number, body: ManufacturerClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/manufacturer/' + id, JSON.stringify(body), this.options)
        .catch(this.handleError);
    }

    public DeleteManufacturer = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/manufacturer/' + id)
        .catch(this.handleError);
    }

    private handleError(error: Response) {
        console.error(error);
        return Observable.throw(error.json().error || 'Server error');
    }
}