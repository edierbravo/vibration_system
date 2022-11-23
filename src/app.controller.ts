import { Body, Controller, Delete, Get, Param, Patch, Post, Put } from '@nestjs/common';
import { AppService } from './app.service';

interface ticket {
  source: string,
  destination: string,
  date: string,
  days: number,
  passengers: number
}

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) { }

  private  tickets: ticket[] = [{
    source: "Popayan",
    destination: "Bogota",
    date: "16 Abril 2022",
    days: 6,
    passengers: 5
  }]

  @Get()
  getHello(): ticket[] {
    return this.tickets;
  }

  @Post()
  crear(@Body() datos: ticket): ticket {
    this.tickets.push(datos);
    return datos;
  }

  @Put(":id")
  modificar(@Body() datos: ticket, @Param('id') id: number): ticket | string {
    try{
    this.tickets[id] = datos
    return this.tickets[id];
    }
    catch{
      return `No fue posible modificar el vuelo en la posición ${id}`
    }
  }

  @Delete(":id")
  eliminar(@Param('id') id: number){
    try{
      this.tickets = this.tickets.filter((val, index) => index != id);
      return true;
    }
    catch{
      return false;
    }
  }

  @Patch(":id/passengers/:passengers")
  changePassengers(@Param('id') id: number, @Param('passengers') passengers: number): ticket | string{
    try{
      this.tickets[id].passengers = passengers;
      return this.tickets[id];
    }
    catch{
      return `No fue posible modificar el vuelo en la posición ${id}`
    }
  }
}