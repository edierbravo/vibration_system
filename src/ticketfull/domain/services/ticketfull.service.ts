import { InsertResult, UpdateResult } from 'typeorm';
import { TicketFullEntity } from '../entities/ticketfull.entity';

export interface TicketFullService {

   list(): Promise<TicketFullEntity[]>;
 
   create(ticketfull: TicketFullEntity): Promise<InsertResult>;
 
   update(id: number, ticketfullData: TicketFullEntity): Promise<UpdateResult>;
 
   delete(id: number): Promise<boolean>;
 
   updateReturn(id: number, retorno: Date): Promise<UpdateResult>;
 }