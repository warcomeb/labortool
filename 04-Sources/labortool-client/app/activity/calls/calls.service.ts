import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../connection/connection.service';
import { ActivityClass } from '../class/activity.class';

@Injectable()
export class CallActivityServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllActivity = (): Observable<Response> => {
        return this.http.get(this.URL + '/activity');
    }

    public GetSingleActivity = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/activity' + id);
    }

    public PostActivity = (item: ActivityClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/activity', toAdd, { headers: this.headers });
    }

    public PutActivity = (item: ActivityClass): Observable<Response> => {
        return this.http.put(this.URL + '/activity', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteActivity = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/activity' + id);
    }

}