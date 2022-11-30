import { Entity, Column, ObjectIdColumn } from 'typeorm';

@Entity('tikectfull')
export class TicketFullEntity {
   @ObjectIdColumn()
   id: number;

   @Column()
   passenger_name: string;

   @Column()
   source: string;

   @Column()
   destination: number;

   @Column()
   goingdate: Date;

   @Column()
   flight: string;

   @Column()
   returndate: Date;
}