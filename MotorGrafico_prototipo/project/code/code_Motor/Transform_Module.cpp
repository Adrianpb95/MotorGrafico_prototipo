/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Transform_Module.hpp"
#include "Transform_Component.hpp"
#include "Entity.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{	
	void Transform_Module::create_component(Entity * entity, xml_node<> * transform_node)
	{		
		shared_ptr<Transform_Component> transform(new Transform_Component(entity));

		transform->parse(transform_node, entity);

		transform_task.add_component(transform);
			
		entity->add("transform", transform);
	}
}