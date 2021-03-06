/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

#ifndef RENDER_TASK_HEADER
#define RENDER_TASK_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Mesh.hpp"
#include "Task.hpp"
#include <vector>

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	class Render_Task : public Task
	{

		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	private:

		vector<shared_ptr<Mesh>> meshes;			///<Conjunto de mallas de la escena


		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:

		////////////////////////////////////////////////////////////
		/// \brief	Constructor de Render_Task:	Inicializa sus componentes
		///	@param	scene				Escena a la que pertenece
		///	@param	priority			Prioridad de la tarea
		///	@param	finished			Tarea finalizada (?)
		////////////////////////////////////////////////////////////
		Render_Task(Scene * scene, int priority = 1, bool finished = false);

		////////////////////////////////////////////////////////////
		/// \brief	SETTER de una malla al conjunto de mallas
		///	@param	mesh				Malla a a�adir
		////////////////////////////////////////////////////////////
		void add_mesh(shared_ptr<Mesh> mesh)
		{
			meshes.push_back(mesh);
		}

		////////////////////////////////////////////////////////////
		/// \brief	GETTER de la ultima malla a�adida. Se usa para conseguir la malla padre de la malla actual. (Solo para mallas hijas)
		///	@param	mesh				Malla a a�adir
		////////////////////////////////////////////////////////////
		shared_ptr<Mesh> get_mesh_parent()
		{
			return meshes.back();
		}

		////////////////////////////////////////////////////////////
		/// \brief	Inicializacion de la tarea: Inicializa los componentes de tipo render
		////////////////////////////////////////////////////////////
		void initialize() override;
		////////////////////////////////////////////////////////////
		/// \brief	Ejecucion de la tarea: Limpia la ventana, renderiza todas las mallas y muestra la ventana
		////////////////////////////////////////////////////////////
		void run() override;
		////////////////////////////////////////////////////////////
		/// \brief	Finalizacion de la tarea: Finaliza los componentes de tipo render
		////////////////////////////////////////////////////////////
		void finalize() override;

	};
}

#endif
