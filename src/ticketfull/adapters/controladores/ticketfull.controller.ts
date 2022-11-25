import { Body, Controller, Delete, Get, Param, Patch, Post, Put } from '@nestjs/common';
import { TicketFullService as TicketFullService } from '../../domain/services/ticketfull.service';

import {TicketFull} from '../../domain/models/ticketfull.model';

const errReturn = (e: Error, message: string) => {
  return {
    message: message,
    error: e
  }
}

@Controller()
export class TicketFullController {
  constructor(private readonly tiketeService: TicketFullService) { }

  @Get()
  getHello() {
    try{
      return this.tiketeService.listar();
    }
    catch(e){
      return errReturn(e, "Error al listar tiketes");
    }
  }

  @Post()
  crear(@Body() datos: TicketFull) {
    try{
      return this.tiketeService.crear(datos);
    }
    catch(e){
      return errReturn(e, "Error al crear tikete");
    }
  }

  @Put(":id")
  modificar(@Body() datos: TicketFull, @Param('id') id: number) {
    try{
      return this.tiketeService.modificar(id, datos);
    }
    catch(e){
      return errReturn(e, "Error al modificar tikete");
    }
  }

  @Delete(":id")
  eliminar(@Param('id') id: number) {
    try{
      return this.tiketeService.eliminar(id);
    }
    catch(e){
      return errReturn(e, "Error al eliminar tikete");
    }
  }

  @Patch(":id/regreso/:regreso")
  cambiarRegreso(@Param('id') id: number, @Param('regreso') regreso: string) {
    try{
      return this.tiketeService.cambiarRegreso(id, regreso);
    }
    catch(e){
      return errReturn(e, "Error al modificar fecha de regreso del tikete");
    }
  }
}