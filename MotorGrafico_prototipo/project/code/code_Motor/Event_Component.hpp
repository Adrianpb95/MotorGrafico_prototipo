/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

#ifndef EVENT_COMPONENT_HEADER
#define EVENT_COMPONENT_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Component.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	class Event_Component : public Component
	{

		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:

		////////////////////////////////////////////////////////////
		/// \brief	Constructor de Event_Component:	Componente de tipo evento con una entidad como padre
		///	@param	entity		Entidad padre
		////////////////////////////////////////////////////////////
		Event_Component(Entity * entity) : Component(entity) {}		

		////////////////////////////////////////////////////////////
		/// \brief	Inicializacion del componente
		////////////////////////////////////////////////////////////
		void initialize() override {}
		////////////////////////////////////////////////////////////
		/// \brief	Ejecucion del componente
		////////////////////////////////////////////////////////////
		void run() override {}
		////////////////////////////////////////////////////////////
		/// \brief	Finalizacion del componente
		////////////////////////////////////////////////////////////
		void finalize() override {}
		////////////////////////////////////////////////////////////
		/// \brief	Lectura de los atributos del componente desde xml
		///	@param	event_node		Nodo del componente en el xml
		///	@param	entity			Entidad padre
		////////////////////////////////////////////////////////////
		void parse(xml_node<> * event_node, Entity * entity) override {}
	};
}
#endif