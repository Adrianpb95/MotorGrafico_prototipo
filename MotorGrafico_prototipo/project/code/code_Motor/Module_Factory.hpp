/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

#ifndef MODULE_FACTORY_HEADER
#define MODULE_FACTORY_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <map>
#include "Render_Module.hpp"
#include "Transform_Module.hpp"
#include "Event_Module.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	class Module_Factory
	{

		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	private:

		typedef shared_ptr<Module>(*Factory) (Scene *scene);		///<Puntero a funcion
		map<string, Factory> modules;								///<Mapa de funciones (tipos de modulo)


		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:		
		
		////////////////////////////////////////////////////////////
		/// \brief	Constructor de Module_Factory:	Registra los tipos de modulo existentes en el motor
		////////////////////////////////////////////////////////////
		Module_Factory()
		{
			add_module("render", Render_Module::create);
			add_module("transform", Transform_Module::create);
			add_module("event", Event_Module::create);
		}

		////////////////////////////////////////////////////////////
		/// \brief	Destructor de Module_Factory
		////////////////////////////////////////////////////////////
		~Module_Factory() 
		{ 
			modules.clear();
		}

		////////////////////////////////////////////////////////////
		/// \brief	Añade un modulo a la fabrica
		///	@param	name		Nombre del modulo
		///	@param	type		Tipo de funcion modulo (Funcion : Render, Transform, Event)
		////////////////////////////////////////////////////////////
		void add_module(const string & name, Factory type)
		{
			modules[name] = type;
		}

		////////////////////////////////////////////////////////////
		/// \brief	Crea un modulo: Si ya existe, lo devuelve y sino crea uno vacio
		///	@param	name		Nombre del modulo a devolver
		///	@param	scene		Tipo de modulo (Render, Transform, Event)
		////////////////////////////////////////////////////////////
		shared_ptr<Module> create_module(const string & name, Scene * scene)
		{			
			if (modules.count(name))
			{				
				return modules[name](scene);
			}
			return shared_ptr<Module>();
		}
	};
}

#endif