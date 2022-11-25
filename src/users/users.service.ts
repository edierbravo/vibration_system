import { Injectable } from '@nestjs/common';

export type User = {
   userId: number,
   username: string,
   password: string
};

@Injectable()
export class UsersService {
   private readonly users: User[] = [
      {
         userId: 1,
         username: 'edier',
         password: 'bravo',
      },
      {
         userId: 2,
         username: 'dario',
         password: 'bravo',
      },
      {
         userId: 2,
         username: 'edier',
         password: 'dario',
      },
   ];

   /**
      * Recupera los datos del usuario
      * @param username Nombre de usuario
      * @returns 
      */
   async findOne(username: string): Promise<User | undefined> {
      return this.users.find(user => user.username === username);
   }
}
