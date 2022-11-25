import { Injectable } from '@nestjs/common';
import {TicketFull} from '../models/ticketfull.model'

@Injectable()
export class TicketFullService {
  cambiarRegreso(id: number, regreso: string) {
    throw new Error('Method not implemented.');
  }
  private ticketfull: TicketFull[] = [{
    passenger_name: "Edier",
    source: "Popayan",
    destination: "Bogota",
    goingdate: '10-10-2022',
    flight: "K34HT8",
    returndate: '11/10/2022'
  }]

  public listar() : TicketFull[] {
    return this.ticketfull
  }

  public crear(tiketefull: TicketFull): TicketFull {
    this.ticketfull.push(tiketefull);
    return tiketefull;
  }

  public modificar(id: number, tiketefull: TicketFull): TicketFull {
      this.ticketfull[id] = tiketefull
      return this.ticketfull[id];
  }

  public eliminar(id: number): boolean {
    const totalTiketesAntes = this.ticketfull.length;
    this.ticketfull = this.ticketfull.filter((val, index) => index != id);
    if(totalTiketesAntes == this.ticketfull.length){
      return false;
    }
    else{
      return true;
    }
  }

   public cambiarReturno(id: number, returnDate: string): TicketFull {
      this.ticketfull[id].returndate = returnDate;
      return this.ticketfull[id];
   }

}