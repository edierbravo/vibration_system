import { InsertResult, UpdateResult } from 'typeorm';
import { TicketFullEntity } from '../entities/ticketfull.entity';

export interface TicketFullService {

   list(): Promise<TicketFullEntity[]>;
 
   create(ticketfull: TicketFullEntity): Promise<InsertResult>;
 
   update(id: string, ticketfullData: TicketFullEntity): Promise<UpdateResult>;
 
   delete(id: string): Promise<boolean>;
 
   updateReturn(id: string, retorno: Date): Promise<UpdateResult>;
 }