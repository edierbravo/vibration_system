import { Body, Controller, Delete, Get, Param, Patch, Post, Put } from '@nestjs/common';
import { AppService } from './app.service';

interface ticket {
  passenger_name: string,
  source: string,
  destination: string,
  goingdate: Date,
  flight: string,
  returndate: Date
}

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) { }

  private  tickets: ticket[] = [{
    passenger_name: "Edier",
    source: "Popayan",
    destination: "Bogota",
    goingdate: new Date(2022-12-25),
    flight: "ABC567",
    returndate: new Date(2022-12-29)
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

  @Patch(":id/returndate/:returndate")
  changePassengers(@Param('id') id: number, @Param('returndate') returndate: Date): ticket | string{
    try{
      this.tickets[id].returndate = returndate;
      return this.tickets[id];
    }
    catch{
      return `No fue posible modificar el vuelo en la posición ${id}`
    }
  }
}