import { Module } from '@nestjs/common';
import { TicketFullController } from './ticketfull/adapters/controladores/ticketfull.controller';
import { TicketFullService } from './ticketfull/domain/services/ticketfull.service';

@Module({
  imports: [],
  controllers: [TicketFullController],
  providers: [TicketFullService],
})
export class AppModule {}
