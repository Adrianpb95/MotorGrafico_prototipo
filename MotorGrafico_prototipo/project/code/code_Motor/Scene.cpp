/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vector>
#include <fstream>
#include <iostream>

#include "Scene.hpp"
#include "Module_Factory.hpp"
#include "Event_Task.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{	
	Scene::Scene(const string & path)
	:	kernel(new Kernel), dispatcher(new Dispatcher())
	{
		//Carga la escena
		load_scene(path);

		//Añade las tareas al kernel por cada modulo contendor
		for (auto & mod : modules) 
		{
			kernel->add(*mod.second->getTask());
		}

		//Lanza el kernel
		kernel->initialize();
	}

	Scene::~Scene()
	{
		entities.clear();
		modules.clear();
		kernel->finalize();
	}

	void Scene::load_scene(const string & path)
	{	
		fstream file(path, fstream::in);

		//Lee el fichero si es correcto
		if (file.good())
		{
			vector<char> content;

			bool end = false;

			while (!end)
			{
				int character = file.get();

				if (character != -1)
				{
					content.push_back((char)character);
				}
				else
				{
					end = true;
				}
			}
			file.close();

			content.push_back(0);

			xml_document<> document;
			document.parse<0>(content.data());

			//Comienza a leer desde el primer nodo (scene)
			xml_node<> * root = document.first_node();

			//Carga la escena
			if (root && string(root->name()) == "scene")
			{				
				parse_scene(root);
			}			
		}		
	}

	View * Scene::parse_scene(xml_node<> * scene_node)	
	{		
		string name;
		string width;
		string height;

		//Guarda los atributos de la escena
		for (xml_attribute<> * attribute = scene_node->first_attribute(); attribute; attribute = attribute->next_attribute())
		{
			if (string(attribute->name()) == "name") name = attribute->value();
			else if (string(attribute->name()) == "width") width = attribute->value();
			else if (string(attribute->name()) == "height") height = attribute->value();
		}
		
		//Crea la ventana
		view = new View(name, stoi(width), stoi(height));

		//Lee todos sus hijos --> entidades
		for 
		(
			xml_node<> * child = scene_node->first_node();
			child; 
			child = child->next_sibling()
		)
		{
			if (child->type() == node_element)
			{
				if (string(child->name()) == "entity")
				{
					parse_entity(child);
				}
			}
		}
		return view;
	}

	void Scene::parse_entity(xml_node<> * entity_node)
	{
		//Crea una entidad
		string name;	
		shared_ptr<Entity> entity(new Entity(this));

		name = entity_node->first_attribute("name")->value();

		//Lee todos sus hijos --> otras entidades hijas y componentes
		for
		(
			xml_node<> * component_node = entity_node->first_node();
			component_node;
			component_node = component_node->next_sibling()
		)
		{									
			if (component_node->type() == node_element)
			{						
				if (string(component_node->name()) == "component")
				{							
					parse_components(component_node, *entity);
				}
				if (string(component_node->name()) == "entity")
				{
					parse_entity(component_node);
				}
			}			
		}
		entities[name] = entity;				
	}

	void Scene::parse_components(xml_node<> * component_node, Entity & entity)
	{
		string type;
			
		//Tipo del componente
		type = component_node->first_attribute("type")->value();

		//Si el tipo de este componente no existe, se crea su modulo		
		if (modules.count(type) == 0)
		{					
			shared_ptr<Module_Factory> mf_aux;
			mf_aux.reset(new Module_Factory());
			modules[type] = mf_aux->create_module(type, this);
		}

		//Se recoge el tipo de modulo y se crea el componente
		Module * module = modules[type].get();
		module->create_component(&entity, component_node);		
	}
}