/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

#ifndef TRANSFORM_COMPONENT_HEADER
#define TRANSFORM_COMPONENT_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Mesh.hpp"
#include "Component.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using std::stof;
namespace example
{
	class Transform_Component : public Component
	{		

		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	private:

		shared_ptr<Mesh> mesh;					///<Puntero de mesh a tratar

		float pos_x, pos_y, pos_z;				///<Posiciones x y z de la malla
		float rot_x, rot_y, rot_z;				///<Rotaciones x y z de la malla
		float angle;							///<Angulo de rotacion de la malla
		float scale;							///<Escala de la malla


		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:	
		
		////////////////////////////////////////////////////////////
		/// \brief	Constructor de Transform_Component: Se inicializan sus variables
		///	@param	entity		Entidad padre
		////////////////////////////////////////////////////////////
		Transform_Component(Entity * entity) : Component(entity),
			pos_x(0), pos_y(0), pos_z(0),
			rot_x(0), rot_y(0), rot_z(0),
			angle(0), scale(0)
		{
		}

		////////////////////////////////////////////////////////////
		/// \brief	Actualiza los valores del componente y mueve la malla con ellos
		///	@param	pos_x_aux		Posicion en x
		///	@param	pos_y_aux		Posicion en y
		///	@param	pos_z_aux		Posicion en z
		///	@param	angle_aux		Angulo de rotacion
		///	@param	scale_aux		Escala
		////////////////////////////////////////////////////////////
		void move(float pos_x_aux, float pos_y_aux, float pos_z_aux, float angle_aux, float scale_aux)
		{
			pos_x += pos_x_aux;
			pos_y += pos_y_aux;
			pos_z += pos_z_aux;

			angle += angle_aux;
			scale += scale_aux;

			mesh->update(angle, scale, pos_x, pos_y, pos_z, rot_x, rot_y, rot_z);
			angle = 0;
		}

		////////////////////////////////////////////////////////////
		/// \brief	GETTER de la posicion de la malla
		////////////////////////////////////////////////////////////
		glm::vec3 get_position() const
		{
			return glm::vec3(pos_x, pos_y, pos_z);
		}

		////////////////////////////////////////////////////////////
		/// \brief	SETTER del puntero a malla
		////////////////////////////////////////////////////////////
		void set_mesh(shared_ptr<Mesh> mesh_aux)
		{
			mesh = mesh_aux;
		}	

		////////////////////////////////////////////////////////////
		/// \brief	Inicializacion del componente
		////////////////////////////////////////////////////////////
		void initialize() override {};
		////////////////////////////////////////////////////////////
		/// \brief	Ejecucion del componente
		////////////////////////////////////////////////////////////
		void run() override;
		////////////////////////////////////////////////////////////
		/// \brief	Finalizacion del componente
		////////////////////////////////////////////////////////////
		void finalize() override {};
		////////////////////////////////////////////////////////////
		/// \brief	Lectura de los atributos del componente desde xml
		///	@param	transform_node		Nodo del componente en el xml
		///	@param	entity			Entidad padre
		////////////////////////////////////////////////////////////
		void parse(xml_node<> * transform_node, Entity * entity) override;
	};
}

#endif