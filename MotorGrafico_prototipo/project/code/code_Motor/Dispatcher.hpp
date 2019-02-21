/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

#ifndef DISPATCHER_HEADER
#define DISPATCHER_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <map>
#include "Message.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	class Dispatcher
	{			

	public:

		struct Listener										///<Struc para crear un Listener
		{
			virtual ~Listener() {}							///<Destructor
			virtual void handle(Message &) = 0;				///<Metodo para recibir el mensaje y llevar a cabo la accion correspondiente
		};

		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	private:

		std::map<int, Listener*> listeners;					///<Conjunto de listeners a gestionar por el dispatcher


		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:
		
		////////////////////////////////////////////////////////////
		/// \brief	Enviar un mensaje si el listener de ese tipo existe
		///	@param	msg				Mensaje a enviar
		////////////////////////////////////////////////////////////
		void send_msg(Message & msg)
		{
			if (listeners.count(msg))
			{
				listeners.begin()->second->handle(msg);
			}
		}

		////////////////////////////////////////////////////////////
		/// \brief	SETTER de un listener con su id en el dispatcher 
		///	@param	id				Identificador (msg) 
		///	@param	listener		Tipo de listener
		////////////////////////////////////////////////////////////
		void add_listener(int id, Listener & listener)
		{
			listeners.insert(std::pair<int, Listener*>(id, &listener));
		}
	};
}

#endif