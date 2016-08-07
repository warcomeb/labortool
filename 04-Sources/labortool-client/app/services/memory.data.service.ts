import {Injectable} from '@angular/core';

@Injectable()
export class MemoryDataService {
    private iD:number = 0;

    constructor() {}

    setID(id) {
        this.iD = id;
    }

    getID() {
        return this.iD;
    }

}