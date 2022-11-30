import { Module } from '@nestjs/common';
import { TicketFullControllerImpl } from './ticketfull/adapters/controladores/ticketfullImpl.controller';
import { TicketFullServiceImpl } from './ticketfull/domain/services/ticketfullImpl.service';
import { AuthModule } from './auth/auth.module';
import { UsersModule } from './users/users.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { TicketFullEntity } from './ticketfull/domain/entities/ticketfull.entity';

@Module({
  imports: [
    AuthModule,
    UsersModule,
    TypeOrmModule.forRoot({
      type: 'mongodb',
      url: 'mongodb+srv://Admin:Admin123db@cluster0.qnvonb3.mongodb.net/?retryWrites=true&w=majority',
      useNewUrlParser: true,
      useUnifiedTopology: true,
      synchronize: true, // Solo para desarrollo
      logging: true,
      autoLoadEntities: true,
    }),
    TypeOrmModule.forFeature([TicketFullEntity])
  ],
  controllers: [TicketFullControllerImpl],
  providers: [
    {
      provide: 'TicketFullService',
      useClass: TicketFullServiceImpl,
    }
  ],
})
export class AppModule {}
