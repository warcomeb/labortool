import {Injectable} from '@angular/core';
import {Http, Response, Headers} from '@angular/http';
import {Observable} from 'rxjs/Rx';
import {HostComponent} from '../configs/host.component';
import {ActiClass, ProdClass, ComponentClass, ProjClass} from '../classes/classes';

@Injectable()
export class CallsService {
    private actionURL: string;
    private headers: Headers;

    constructor(private _http: Http, private _host: HostComponent) {
        this.actionURL = _host.serverURL;

        this.headers = new Headers();
        this.headers.append('Content-Type', 'application/json');
        this.headers.append('Accept', 'application/json');
    }

    // example
    /*public GetAll = (): Observable<Response> => {
        return this._http.get(this.actionURL);
    }*/

    /* GetAll calls */
    public GetAllActivity = ():Observable<Response> => {
        return this._http.get(this.actionURL + '/activity');
    }

    public GetAllProduction = ():Observable<Response> => {
        return this._http.get(this.actionURL + '/activity');
    }

    public GetAllProject = ():Observable<Response> => {
        return this._http.get(this.actionURL + '/activity');
    }

    public GetAllComponent = ():Observable<Response> => {
        return this._http.get(this.actionURL + '/inventory');
    }


    // example
    /*public GetSingle = (id:number): Observable<Response> => {
        return this._http.get(this.actionURL + id);
    }*/

    /* GetSingle calls */
    public GetSingleActivity = (id:number):Observable<Response> => {
        return this._http.get(this.actionURL + '/activity' + id);
    }

    public GetSingleProduction = (id:number):Observable<Response> => {
        return this._http.get(this.actionURL + '/production' + id);
    }

    public GetSingleProject= (id:number):Observable<Response> => {
        return this._http.get(this.actionURL + '/project' + id);
    }

    public GetSingleComponent = (id:number):Observable<Response> => {
        return this._http.get(this.actionURL + '/component' + id);
    }

    // example
    /*public POST = (itemName: string): Observable<Response> => {
        var toAdd = JSON.stringify({ItemName: itemName});
        return this._http.post(this.actionURL, toAdd, {headers:this.headers});
    }*/

    /* Post Calls */
    public PostActivity = (item:ActiClass):Observable<Response> => {
        var toAdd = JSON.stringify({Item:item});
        return this._http.post(this.actionURL + '/activity', toAdd, {headers: this.headers});
    }

    public PostProduction = (item:ProdClass):Observable<Response> => {
        var toAdd = JSON.stringify({Item:item});
        return this._http.post(this.actionURL + '/production', toAdd, {headers:this.headers});
    }

    public PostComponent = (item:ComponentClass):Observable<Response> => {
        var toAdd = JSON.stringify({Item:item});
        return this._http.post(this.actionURL + '/inventory', toAdd, {headers:this.headers});

    }

    public PostProject = (item:ProjClass):Observable<Response> => {
        var toAdd = JSON.stringify({Item:item});
        return this._http.post(this.actionURL + '/project', toAdd, {headers:this.headers});
    }
    
    // example
    /*public PUT = (itemToUpdate:string):Observable<Response> => {
        return this._http.put(this.actionURL, JSON.stringify(itemToUpdate), { headers: this.headers });
    }*/

    /* Put Calls */
    public PutActivity = (item:ActiClass):Observable<Response> => {
        return this._http.put(this.actionURL, JSON.stringify(item), {headers:this.headers});
    }

    public PutProduction = (item:ProdClass):Observable<Response> => {
        return this._http.put(this.actionURL, JSON.stringify(item), {headers:this.headers});
    }

    public PutProject = (item:ProjClass):Observable<Response> => {
        return this._http.put(this.actionURL, JSON.stringify(item), {headers:this.headers});
    }

    public PutComponent = (item:ComponentClass):Observable<Response> => {
        return this._http.put(this.actionURL, JSON.stringify(item), {headers:this.headers});
    }

    // example
    /*public DELETE = (id: number): Observable<Response> => {
            return this._http.delete(this.actionURL + id);
    }*/

    /* Delete Calls */
    public DeleteActivity = (id:number):Observable<Response> => {
        return this._http.delete(this.actionURL + '/activity' + id);
    }

    public DeleteProduction = (id:number):Observable<Response> => {
        return this._http.delete(this.actionURL + '/production' + id);
    }

    public DeleteProject = (id:number):Observable<Response> => {
        return this._http.delete(this.actionURL + '/project' + id);
    }

    public DeleteComponent = (id:number):Observable<Response> => {
        return this._http.delete(this.actionURL + '/inventory' + id);
    }
}