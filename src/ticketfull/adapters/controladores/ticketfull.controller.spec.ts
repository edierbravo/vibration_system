import { Test, TestingModule } from '@nestjs/testing';
import { TicketFullController as TicketFullController } from './ticketfull.controller';
import { TicketFullService as TicketFullService } from '../../domain/services/ticketfull.service';

describe('AppController', () => {
  let appController: TicketFullController;

  beforeEach(async () => {
    const app: TestingModule = await Test.createTestingModule({
      controllers: [TicketFullController],
      providers: [TicketFullService],
    }).compile();

    appController = app.get<TicketFullController>(TicketFullController);
  });

  describe('root', () => {
    it('should return "Hello World!"', () => {
      expect(appController.getHello()).toBe('Hello World!');
    });
  });
});