import { Body, Controller, Delete, Get, Inject, Param, Patch, Post, Put, UseGuards } from '@nestjs/common';
import { TicketFullService } from '../../domain/services/ticketfull.service';

import { TicketFullEntity } from 'src/ticketfull/domain/entities/ticketfull.entity';
import { TicketFullController } from './ticketfull.controller';

import { JwtAuthGuard } from 'src/auth/jwt-auth.guards';

const errReturn = (e: Error, message: string) => {
  return {
    message: message,
    error: e
  }
}

@Controller()
export class TicketFullControllerImpl implements TicketFullController {
  constructor(@Inject('TicketFullService') private readonly tiketeService: TicketFullService) { }

  @Get()
  listTicketsFull() {
    try{
      return this.tiketeService.list();
    }
    catch(e){
      return errReturn(e, "Error al listar tiquetes");
    }
  }

  @UseGuards(JwtAuthGuard)
  @Post()
  create(@Body() datos: TicketFullEntity) {
    try{
      return this.tiketeService.create(datos);
    }
    catch(e){
      return errReturn(e, "Error al crear tiquete");
    }
  }
  
  @Put(":id")
  update(@Body() datos: TicketFullEntity, @Param('id') id: number) {
    try{
      return this.tiketeService.update(id, datos);
    }
    catch(e){
      return errReturn(e, "Error al modificar tiquete");
    }
  }
  @UseGuards(JwtAuthGuard)
  @Delete(":id")
  delete(@Param('id') id: number) {
    try{
      return this.tiketeService.delete(id);
    }
    catch(e){
      return errReturn(e, "Error al eliminar fecha de regreso del tiquete");
    }
  }
  @UseGuards(JwtAuthGuard)
  @Patch(":id/regreso/:regreso")
  updateReturn(@Param('id') id: number, @Param('regreso') regreso: Date) {
    try{
      return this.tiketeService.updateReturn(id, regreso);
    }
    catch(e){
      return errReturn(e, "Error al modificar fecha de regreso del tiquete");
    }
  }
}