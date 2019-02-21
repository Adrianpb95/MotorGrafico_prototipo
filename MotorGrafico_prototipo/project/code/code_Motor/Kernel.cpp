/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Kernel.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	void Kernel::initialize()
	{
		//Lanzamiento de cada tarea
		for (auto & task : tasks)
		{
			task->initialize();
		}
	}

	void Kernel::execute()
	{
		//Mientras esta activo, ejecutamos cada tarea
		do
		{	
			for (auto task : tasks)
			{				
				task->run();

				if (task->is_finished())
				{
					task->finalize();
					tasks.remove(task);
				}				
			}
		}
		while (running);		
		finalize();
	}

	void Kernel::finalize()
	{
		//Cuando se desactiva, finalizamos cada tarea
		for (auto & task : tasks)
		{
			task->finalize();
		}
	}
}