
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Ángel on march of 2018                                          *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/*
	EDITED BY:
	ADRIAN PONCE BALSEIRO
	ESNE G4.3 DDVJ
	adrianpb95@gmail.com
	10 / 06 / 2018
*/

#ifndef MESH_HEADER
#define MESH_HEADER


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "Material.hpp"
#include <memory>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>
#include "Camera.hpp"
#include <Point.hpp>
#include <vector>
#include <list>
#include <SFML/OpenGL.hpp>


////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using namespace std;
using namespace toolkit;

namespace example
{
	class Material;
	class Mesh
	{

		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	private:

		
		enum											
		{
			COORDINATES_VBO,
			TEXTURE_UVS_VBO,
			NORMALS_VBO,
			INDICES_IBO,
			VBO_COUNT
		};													///<Índices para indexar el array vbo_ids:

		std::string					error;					///<String de error del tinyobj 		

		GLuint vbo_ids[VBO_COUNT];							///<Ids de los VBOs que se usan
		
		vector< int >	original_indices;					///<Array de indices de la malla 

		GLuint vao_id;										///<ID del VAO 

		float angle;										///<Angulo de giro de la malla
		glm::vec3 position;									///<Posicion de la malla
		glm::vec3 scale;									///<Escala de la malla
		list<shared_ptr<Mesh>>	children;					///<Lista de hijos para el grafo de escena

		std::shared_ptr<Material> material;					///<Material de la malla
		glm::vec3 rotation;

		bool render_b;


		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:

		Mesh() {}

		////////////////////////////////////////////////////////////
		/// \brief	Constructor de Mesh:	Recibe los parametros del tinyobj, los ordena y genera los VBOs (Vertices, normales, indices y texturas)
		///	@param	material_aux		Material de la malla
		///	@param	obj_file_path		Ruta de la malla
		////////////////////////////////////////////////////////////
		Mesh(std::shared_ptr<Material> &material_aux, const string &obj_file_path);

		////////////////////////////////////////////////////////////
		/// \brief	Destructor de Mesh: Se liberan los VBOs usados
		////////////////////////////////////////////////////////////
		~Mesh();

		void set_render(bool render_aux) 
		{
			render_b = render_aux;
		}
		
		////////////////////////////////////////////////////////////
		/// \brief	Dibuja la malla y sus hijos:	Pinta el material y actualiza la matriz de transformacion y de normales
		///	@param	model_view_matrix_parent		Matriz de transformacion del padre
		////////////////////////////////////////////////////////////
		void render(glm::mat4 model_view_matrix_parent);
		
		////////////////////////////////////////////////////////////
		/// \brief	Actualiza el movimiento de la mesh y de sus hijos
		///	@param	angle		Angulo de rotacion
		///	@param	scale		Escala de la mesh
		///	@param	pos_x		Posicion x de la mesh
		///	@param	pos_y		Posicion y de la mesh
		///	@param	pos_z		Posicion z de la mesh
		///	@param	rot_x		Rotacion x de la mesh
		///	@param	rot_y		Rotacion y de la mesh
		///	@param	rot_z		Rotacion z de la mesh
		////////////////////////////////////////////////////////////
		void update(float angle, float scale, float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z);

		////////////////////////////////////////////////////////////
		/// \brief	Añade una malla como hija de otra
		///	@param	m			Malla hija
		////////////////////////////////////////////////////////////
		void add(shared_ptr <Mesh> & m);
	};

}

#endif
