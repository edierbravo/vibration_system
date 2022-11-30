import { TicketFull } from "../models/ticketfull.model";

export interface TicketFullService {

   /**
    * Retorna la lista de tiquetes registrados
    */
   list(): TicketFull[];

   /**
    * Crea un nuevo tiquete
    * @param ticketfull datos del nuevo tiquete
    * @return Nuevo tiquete
    */
   create(ticketfull: TicketFull): TicketFull;

   /**
    * Actualiza datos del tiquete
    * @param id Identificador único del tiquete
    * @param ticketfull datos del tiquete
    * @return tiquete modificado
    */
   update(id: number, ticketfull: TicketFull): TicketFull

   /**
    * Eliminar un tiquete
    * @param id Identificador único del tiquete
    * @return True si eliminó al tikete
    */
   delete(id: number): boolean

   /**
    * Cambia la fecha de regrerso de un tiquete
    * @param id Identificador único del tiquete
    * @param returndate nuevo valor de la fecha de regreso 
    */
   updateReturn(id: number, returndate: Date): TicketFull
}