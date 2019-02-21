/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "Render_Task.hpp"
#include "Scene.hpp"

namespace example
{
	Render_Task::Render_Task(Scene * scene, int priority, bool finished)
		: Task(scene, priority, finished)
	{				
	}

	void Render_Task::initialize()
	{
		for (auto & component : components)
		{
			component->initialize();
		}
	}

	void Render_Task::run()
	{	
		//limpia los buffers de la ventana
		scene->get_view()->clear_view();

		//renderiza todas las mallas
		for (auto & mesh : meshes) 
		{
			mesh->render(scene->get_view()->get_camera_model_view());
		}

		//Muestra la ventana
		scene->get_view()->display_view();
	}

	void Render_Task::finalize()
	{
		for (auto & component : components)
		{
			component->finalize();
		}
	}


}