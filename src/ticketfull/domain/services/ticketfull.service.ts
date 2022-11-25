import { TicketFull } from "../models/ticketfull.model";

export interface TicketFullService {

   /**
    * Retorna la lista de tiketes registrados
    */
   list(): TicketFull[];

   /**
    * Crea un nuevo tikete
    * @param ticketfull datos del nuevo tikete
    * @return Nuevo tikete
    */
   create(ticketfull: TicketFull): TicketFull;

   /**
    * Actualiza datos del tikete
    * @param id Identificador único del tikete
    * @param ticketfull datos del tikete
    * @return tikete modificado
    */
   update(id: number, ticketfull: TicketFull): TicketFull

   /**
    * Eliminar un tikete
    * @param id Identificador único del tikete
    * @return True si eliminó al tikete
    */
   delete(id: number): boolean

   /**
    * Cambia la fecha de regrerso de un tikete
    * @param id Identificador único del tikete
    * @param returndate nuevo valor de la fecha de regreso 
    */
   updateReturn(id: number, returndate: Date): TicketFull
}