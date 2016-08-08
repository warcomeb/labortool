import { Injectable } from '@angular/core';

@Injectable()
export class DataService {
    private ID: number = 0;

    constructor() {}

    setID(id) {
        this.ID = id;
    }

    getID() {
        return this.ID;
    }

}