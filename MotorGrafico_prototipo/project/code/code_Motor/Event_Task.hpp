/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

#ifndef EVENT_TASK_HEADER
#define EVENT_TASK_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Task.hpp"
#include "Message.hpp"
#include "Event_Updater.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	class Event_Task : public Task
	{

		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	private:

		Event event;					///<Evento de sfml para registrar los inputs del usuario
		Window * window;				///<Ventana de sfml
		Event_Updater * updater;		///<Updater que actualiza el mov del jugador y la mision

		Message move_up;				///<Mensaje : Movimiento hacia arriba
		Message move_down;				///<Mensaje : Movimiento hacia abajo
		Message move_right;				///<Mensaje : Movimiento hacia derecha
		Message move_left;				///<Mensaje : Movimiento hacia izquierda
		Message turn_right;				///<Mensaje : Rotacion a la derecha
		Message turn_left;				///<Mensaje : Rotacion a la izquierda
		

		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:

		////////////////////////////////////////////////////////////
		/// \brief	Constructor de Event_Task:	Inicializa sus componentes
		///	@param	scene				Escena a la que pertenece
		///	@param	priority			Prioridad de la tarea
		///	@param	finished			Tarea finalizada (?)
		////////////////////////////////////////////////////////////
		Event_Task(Scene * scene, int priority = 2, bool finished = false);

		////////////////////////////////////////////////////////////
		/// \brief	Inicializacion de la tarea: Inicializa los componentes de tipo evento
		////////////////////////////////////////////////////////////
		void initialize() override;
		////////////////////////////////////////////////////////////
		/// \brief	Ejecucion de la tarea: Cerrar ventana, cambiar tamaño de ventana y gestion de inputs del jugador
		////////////////////////////////////////////////////////////
		void run() override;
		////////////////////////////////////////////////////////////
		/// \brief	Finalizacion de la tarea: Finaliza los componentes de tipo evento
		////////////////////////////////////////////////////////////
		void finalize() override;	

	
	};
}

#endif