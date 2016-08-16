import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Rx';
import { ConnectionService } from '../../../connection/connection.service';
import { ManufacturerClass } from '../class/manufacturer.class';

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

    public GetAllManufacturer = (): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/manufacturer');
    }

    public GetSingleManufacturer = (id: number): Observable<Response> => {
        return this.http.get(this.URL + '/inventory/manufacturer/' + id);
    }

    public PostManufacturer = (item: ManufacturerClass): Observable<Response> => {
        var toAdd = JSON.stringify({Item: item});
        return this.http.post(this.URL + '/inventory/manufacturer', toAdd, { headers: this.headers });
    }

    public PutManufacturer = (item: ManufacturerClass): Observable<Response> => {
        return this.http.put(this.URL + '/inventory/manufacturer', JSON.stringify(item), { headers: this.headers });
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