import { Module } from '@nestjs/common';
import { TicketFullControllerImpl } from './ticketfull/adapters/controladores/ticketfullImpl.controller';
import { TicketFullServiceImpl } from './ticketfull/domain/services/ticketfullImpl.service';
import { AuthModule } from './auth/auth.module';
import { UsersModule } from './users/users.module';

@Module({
  imports: [AuthModule, UsersModule],
  controllers: [TicketFullControllerImpl],
  providers: [
    {
      provide: 'TicketFullService',
      useClass: TicketFullServiceImpl,
    }
  ],
})
export class AppModule {}