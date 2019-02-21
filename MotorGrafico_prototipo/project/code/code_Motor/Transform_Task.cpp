/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Transform_Task.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	Transform_Task::Transform_Task(Scene * scene, int priority, bool finished)
		: Task(scene, priority, finished)
	{
	}

	void Transform_Task::initialize()
	{		
		for (auto & component : components)
		{
			component->initialize();
		}
	}

	void Transform_Task::run()
	{		
		for (auto & component : components)
		{			
			component->run();			
		}
	}	

	void Transform_Task::finalize()
	{
		for (auto & component : components)
		{
			component->finalize();
		}
	}
}