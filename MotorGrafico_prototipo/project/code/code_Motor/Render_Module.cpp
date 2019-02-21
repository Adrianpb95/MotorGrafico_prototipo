/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Render_Module.hpp"
#include "Render_Component.hpp"
#include "Entity.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	void Render_Module::create_component(Entity * entity, xml_node<> * render_node)
	{	
		shared_ptr<Render_Component> mesh_component(new Render_Component(entity));

		mesh_component->parse(render_node, entity);

		render_task.add_component(mesh_component);

		//Si es una mesh hija de otra, se añade al padre para que se encarge de renderizarla
		if (mesh_component->is_child())
		{
			render_task.get_mesh_parent()->add(mesh_component->get_mesh());
		}
		//Sino, la renderiza la tarea
		else 
		{
			render_task.add_mesh(mesh_component->get_mesh());
		}		
					
		entity->add("render", mesh_component);
	}
}
