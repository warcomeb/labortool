import { Injectable } from '@angular/core';
import { Http, Response, Headers, RequestOptions } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { LocationClass } from '../class/location.class';

@Injectable()
export class CallLocationServices {
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

    public GetAllLocation = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/location')
        .catch(this.handleError);
    }

    public GetSingleLocation = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/location/' + id)
        .catch(this.handleError);
    }

    public PostLocation = (body: LocationClass): Observable<Response> => {
        return this.http.post(this.URL + '/inventory/location', JSON.stringify(body), this.options)
        .catch(this.handleError);
    }

    public PutLocation = (id: number, body: LocationClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/location/' + id, JSON.stringify(body), this.options)
        .catch(this.handleError);
    }

    public DeleteLocation = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/inventory/location/' + id)
        .catch(this.handleError);
    }

    private handleError(error: Response) {
        console.error(error);
        return Observable.throw(error.json().error || 'Server error');
    }

}