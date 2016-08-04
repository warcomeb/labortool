import {Injectable} from '@angular/core';
import {ActivityClass} from '../classes/classes';

@Injectable()
export class Fake_DataService {
    public MyActivity:ActivityClass[] = [
        { Id:1, Title:'prova', Description:'prova1', WorkCode:'1234', Deadline:new Date(2016, 0, 0), Priority:3, Status:5, Type:3, Employee: 1, Editable:1, Notes:'sadadsa'}
    ];
}