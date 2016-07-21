import {Injectable} from '@angular/core';
import {Http, Response, Headers} from '@angular/http';
import {Observable} from 'rxjs/Rx';
import {HostComponent} from '../configs/host.component';

@Injectable()
export class CallsService {
    public numeroID: number = 0;
    private actionURL: string;
    private headers: Headers;

    constructor(private _http: Http, private _host: HostComponent) {
        this.actionURL = _host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    /* Get calls */
    public GetAll = (): Observable<Response> => {
        return this._http.get(this.actionURL);
    }

    public GetAllActivity = (): Observable<Response> => {
        return this._http.get(this.actionURL + '/activity');
    }

    public GetActivity = (): Observable<Response> => {
        return this._http.get(this.actionURL + '/activity/?id=' + this.numeroID);
    }

    
    // mai provata
    public GetSingle = (id: number): Observable<Response> => {
        return this._http.get(this.actionURL + id);
    }
    
    // mai provata
    public POST = (itemName: string): Observable<Response> => {
        var toAdd = JSON.stringify({ItemName: itemName});
        return this._http.post(this.actionURL, toAdd, {headers: this.headers});
    }

    public PUT = (itemToUpdate: string): Observable<Response> => {
        return this._http.put(this.actionURL, JSON.stringify(itemToUpdate), {headers: this.headers});
    }
    
    // mai provata
    public DELETE = (id: number): Observable<Response> => {
        return this._http.delete(this.actionURL + id);
    }
}