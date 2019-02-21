/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Event_Module.hpp"
#include "Entity.hpp"
#include "Event_Component.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	void Event_Module::create_component(Entity * entity, xml_node<> * event_node)
	{		
		shared_ptr<Event_Component> event(new Event_Component(entity));
				
		event->parse(event_node, entity);
	
		event_task.add_component(event);

		entity->add("event", event);		
	}
}
