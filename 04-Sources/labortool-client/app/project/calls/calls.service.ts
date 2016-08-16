import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../connection/connection.service';
import { ProjectClass } from '../class/project.class';

@Injectable()
export class CallProjectServices {
    private URL: string;
    private headers: Headers;

    constructor(private http: Http, private host: ConnectionService) {
        this.URL = host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    public GetAllProject = (): Observable<Response> => {
        return this.http.get(this.URL + '/project');
    }

    public GetSingleProject = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/project' + id);
    }

    public PostProject = (item: ProjectClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/project', toAdd, { headers: this.headers });
    }

    public PutProject = (item: ProjectClass): Observable<Response> => {
        return this.http.put(this.URL + '/project', JSON.stringify(item), { headers: this.headers });
    }

    public DeleteProject = (id: number): Observable<Response> => {
        return this.http.delete(this.URL + '/project' + id);
    }

}