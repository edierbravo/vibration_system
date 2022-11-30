import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { InsertResult, MongoRepository, UpdateResult } from 'typeorm';
/*import { TicketFull } from '../models/ticketfull.model';*/
import { TicketFullEntity } from '../entities/ticketfull.entity';
import { TicketFullService } from './ticketfull.service';

@Injectable()
export class TicketFullServiceImpl implements TicketFullService {
  constructor(
    @InjectRepository(TicketFullEntity)
    private repository: MongoRepository<TicketFullEntity>,
  ) {}

  public async list(): Promise<TicketFullEntity[]> {
    return await this.repository.find();
  }
 
  public async create(ticketfullData: TicketFullEntity): Promise<InsertResult> {
    const newTicketFull = await this.repository.insert(ticketfullData);
    return newTicketFull;
  }
 
  public async update(
    id: number,
    ticketfullData: TicketFullEntity,
  ): Promise<UpdateResult> {
    const updatedTicketFull = await this.repository.update(id, ticketfullData);
    return updatedTicketFull;
  }
 
  public async delete(id: number): Promise<boolean> {
    const deleteResult = await this.repository.delete(id);
    return deleteResult.affected > 0;
  }
 
  public async updateReturn(id: number, retorno: Date): Promise<UpdateResult> {
    const updatedTicketFull = await this.repository.update(id, { returndate: retorno });
    return updatedTicketFull;
  }
}