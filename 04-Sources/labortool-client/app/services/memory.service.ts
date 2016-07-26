import {Injectable} from '@angular/core';
import {ClassActivity} from '../classes/activity.class';

@Injectable()
export class MemoryService {
    public ServerActivity: ClassActivity;
    
    constructor() {}

    setValue(val) {
        this.ServerActivity = val;
    }

   /*getValue(val) {
        return this.val;
    }*/

}