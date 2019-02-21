/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Render_Component.hpp"
#include "Transform_Component.hpp"
#include "Scene.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	void Render_Component::initialize()
	{		
		//Se setea la malla a un transform para poder manejarla
		Transform_Component * mesh_transform = dynamic_cast<Transform_Component*>(parent->get_component("transform").get());	
		mesh_transform->set_mesh(mesh);
	}

	void Render_Component::parse(xml_node<> * mesh_node, Entity * entity)
	{		
		string name;
		string mesh_path;
		string material_path;
		string child;

		shared_ptr<Material> material;		

		//Se guardan los atributos de la malla
		for (xml_attribute<> * attribute = mesh_node->first_attribute(); attribute; attribute = attribute->next_attribute())
		{
			if (string(attribute->name()) == "name") name = attribute->value();
			else if (string(attribute->name()) == "mesh_path") mesh_path = attribute->value();
			else if (string(attribute->name()) == "material_path") 
			{				
				material_path = attribute->value();
				material.reset(new Material(material_path.c_str()));				
				
				Scene * scene_aux = entity->get_parent();
				scene_aux->get_view()->set_material(name, material);
			}
			else if (string(attribute->name()) == "child") 
			{
				child = attribute->value();
				if (child == "true") child_b = true;
			} 
		}		
		//Se crea la malla con la informacion obtenida
		mesh.reset(new Mesh(material, mesh_path));
	}

	
}