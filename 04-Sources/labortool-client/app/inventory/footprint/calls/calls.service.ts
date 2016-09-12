import { Injectable } from '@angular/core';
import { Http, Response, Headers, RequestOptions } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { FootprintClass } from '../class/footprint.class';

@Injectable()
export class CallFootprintServices {
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

    public GetAllFootprint = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/footprint')
        .catch(this.handleError);
    }

    public GetSingleFootprint = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/footprint/' + id)
        .catch(this.handleError);
    }

    public PostFootprint = (body: FootprintClass): Observable<Response> => {
        return this.http.post(this.URL + '/inventory/footprint', JSON.stringify(body), this.options)
        .catch(this.handleError);
    }

    public PutFootprint = (id: number, body: FootprintClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/footprint/' + id, JSON.stringify(body), this.options)
        .catch(this.handleError);
    }

    public DeleteFootprint = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/footprint/' + id)
        .catch(this.handleError);
    }

    private handleError(error: Response) {
        console.error(error);
        return Observable.throw(error.json().error || 'Server error');
    }
}