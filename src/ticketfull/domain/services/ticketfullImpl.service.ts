import { Injectable } from '@nestjs/common';
import { TicketFull } from '../models/ticketfull.model';
import { TicketFullService } from './ticketfull.service';
import { TicketFullEntity } from '../entities/ticketfull.entity';
import { InjectRepository } from '@nestjs/typeorm';
import { MongoRepository } from 'typeorm';

@Injectable()
export class TicketFullServiceImpl implements TicketFullService {
  constructor(
    @InjectRepository(TicketFullEntity)
    private repository: MongoRepository<TicketFullEntity>,
 ) {}

  private Ticketfull: TicketFull[] = [{
    passenger_name: "Edier",
    source: "Popayan",
    destination: "Bogota",
    goingdate: new Date("2022-12-10"), 
    flight: "456TYG",
    returndate: new Date("2022-12-20"),
  }]

  public list() : TicketFull[] {
    return this.Ticketfull
  }

  public create(tikete: TicketFull): TicketFull {
    this.Ticketfull.push(tikete);
    return tikete;
  }

  public update(id: number, tikete: TicketFull): TicketFull {
      this.Ticketfull[id] = tikete
      return this.Ticketfull[id];
  }

  public delete(id: number): boolean {
    const totalTiketesAntes = this.Ticketfull.length;
    this.Ticketfull = this.Ticketfull.filter((val, index) => index != id);
    if(totalTiketesAntes == this.Ticketfull.length){
      return false;
    }
    else{
      return true;
    }
  }

   public updateReturn(id: number, retorno: Date): TicketFull {
      this.Ticketfull[id].returndate = retorno;
      return this.Ticketfull[id];
   }

}