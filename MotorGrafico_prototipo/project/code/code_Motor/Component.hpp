/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include "rapidxml.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using namespace rapidxml;
namespace example
{
	class Entity;
	class Component
	{

		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	protected:
		
		Entity * parent;			///<Padre del componente (Entidad)


		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:
		
		////////////////////////////////////////////////////////////
		/// \brief	Constructor de Component:	Crea el componente y registra su entidad padre
		///	@param	entity						Entidad padre
		////////////////////////////////////////////////////////////
		Component(Entity * entity);

		////////////////////////////////////////////////////////////
		/// \brief	Destructor de Component
		////////////////////////////////////////////////////////////
		~Component();

		////////////////////////////////////////////////////////////
		/// \brief	GETTER del padre
		////////////////////////////////////////////////////////////
		Entity * get_parent()
		{
			return parent;
		}	
		
		////////////////////////////////////////////////////////////
		/// \brief	Inicializacion del componente
		////////////////////////////////////////////////////////////
		virtual void initialize() = 0;		
		////////////////////////////////////////////////////////////
		/// \brief	Ejecucion del componente
		////////////////////////////////////////////////////////////
		virtual void run() = 0;
		////////////////////////////////////////////////////////////
		/// \brief	Finalizacion del componente
		////////////////////////////////////////////////////////////
		virtual void finalize() = 0;
		////////////////////////////////////////////////////////////
		/// \brief	Lectura de los atributos del componente desde xml
		///	@param	node		Nodo del componente en el xml
		///	@param	entity		Entidad padre
		////////////////////////////////////////////////////////////
		virtual void parse(xml_node<> * node, Entity * entity) {} 
	};
}

#endif
