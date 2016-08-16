import { Component } from '@angular/core';
import { ROUTER_DIRECTIVES }  from '@angular/router';

import { DataService } from './data/data.service';

@Component({
  selector: 'my-app',
  templateUrl: './app/app.component.html',
  styleUrls: ['./app/app.component.css'],
  directives: [ROUTER_DIRECTIVES],
  providers: [DataService]
})

export class AppComponent { 
    private prova:string = "My First Angular 2 App";
}