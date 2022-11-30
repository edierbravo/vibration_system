import { TicketFullEntity } from 'src/ticketfull/domain/entities/ticketfull.entity';

export interface TicketFullController {
  /**
   *  Retorna la lista de Tiketes de ida y vuelta
   */
  listTicketsFull();

  /**
   * Crea un tikete
   * @param datos Objeto con datos del tikete
   */
  create(datos: TicketFullEntity);

  /**
   * Modifica datos de un tikete
   * @param datos Objeto con datos de tikete
   * @param id Identificador único del tikete
   */
  update(datos: TicketFullEntity, id: number);

  /**
   * Elimina un tikete
   * @param id Identificador único del tikete
   */
  delete(id: number);

  /**
   * Cambia fecha de regrrso del tikete
   * @param id Identificador único del tikete
   * @param returndate fecha de regreso del vuelo
   */
  updateReturn(id: number, returndate: Date);
}