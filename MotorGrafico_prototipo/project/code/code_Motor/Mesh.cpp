
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

#define TINYOBJLOADER_IMPLEMENTATION


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vector>
#include "Mesh.hpp"
#include "Color_Buffer_Rgba8888.hpp"
#include "tiny_obj_loader.h"

#include <iostream>

#include "Vertex_Shader.hpp"
#include "Fragment_Shader.hpp"
#include "Material_Shaders.hpp"



////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using std::vector;
using namespace tinyobj;

extern "C"
{
#include <targa.h>
}

namespace example
{
	// Se definen los datos de la malla:	
	Mesh::Mesh(std::shared_ptr<Material> &material_aux, const string &obj_file_path)
		:
		material(material_aux)
	{

		attrib_t             attributes;
		std::vector< shape_t    > shapes;
		std::vector< material_t > materials;

		vector< float > vertex_components;					
		vector< float > normal_components;					
		vector< float > text_components;																			

		//Se cargan estos datos con el tinyobj y se detecta si falta algo
		if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, obj_file_path.c_str()) || !error.empty())
		{
			return;
		}

		if (shapes.size() == 0) { error = std::string("There're no shapes in ") + obj_file_path; return; }
		if (attributes.vertices.size() == 0) { error = std::string("There're no vertices in ") + obj_file_path; return; }
		if (attributes.normals.size() == 0) { error = std::string("There're no normals in ") + obj_file_path; return; }
		if (attributes.texcoords.size() == 0) { error = std::string("There're no texture coord in ") + obj_file_path; return; }
		
		angle = 0.f;
		position = glm::vec3(0.f, 0.f, -5.f);
		scale = glm::vec3(1.f, 1.f, 1.f);
		rotation = glm::vec3(1.f, 1.f, 1.f);
		render_b = true;


		

		vertex_components.resize(shapes[0].mesh.indices.size() * 3);
		normal_components.resize(shapes[0].mesh.indices.size() * 3);
		text_components.resize(shapes[0].mesh.indices.size() * 2);


		for (auto & shapes : shapes)
		{
			const vector< index_t > & indices = shapes.mesh.indices;
			const size_t             indices_count = (size_t)indices.size();

			if (indices_count > 0)
			{
				const size_t   vertices_count = indices_count;

				//Se guardan los vertices, las normales y se ordenan los indices
				for (size_t src = 0, dst = 0, text = 0; src < indices_count; ++src, dst += 3, text += 2)
				{
					int vertex_src = indices[src].vertex_index * 3;
					int normal_src = indices[src].normal_index * 3;
					int text_scr = indices[src].texcoord_index * 2;

					vertex_components[dst + 0] = attributes.vertices[vertex_src + 0];
					vertex_components[dst + 1] = attributes.vertices[vertex_src + 1];
					vertex_components[dst + 2] = attributes.vertices[vertex_src + 2];

					normal_components[dst + 0] = attributes.normals[normal_src + 0];
					normal_components[dst + 1] = attributes.normals[normal_src + 1];
					normal_components[dst + 2] = attributes.normals[normal_src + 2];

					text_components[text + 0] = attributes.texcoords[text_scr + 0];
					text_components[text + 1] = attributes.texcoords[text_scr + 1];

					original_indices.push_back(src);
				}
			}		

		// Se generan índices para los VBOs del cubo:
			glGenBuffers(VBO_COUNT, vbo_ids);
			//Se generan los indices de los VAOs
			glGenVertexArrays(1, &vao_id);
			glBindVertexArray(vao_id);

			// Se suben a un VBO los datos de coordenadas:
			glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
			glBufferData(GL_ARRAY_BUFFER, vertex_components.size() * sizeof(float), vertex_components.data(), GL_STATIC_DRAW);
			//VertexAtributes
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Se suben a un VBO los datos de textura y se vinculan al VAO:
			glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[TEXTURE_UVS_VBO]);
			glBufferData(GL_ARRAY_BUFFER, text_components.size() * sizeof(float), text_components.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

			//Se suben a un VBO los datos de normales:
			glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
			glBufferData(GL_ARRAY_BUFFER, normal_components.size() * sizeof(float), normal_components.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

			// Se suben a un VBO los datos de índices:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_IBO]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, original_indices.size() * sizeof(GLuint), original_indices.data(), GL_STATIC_DRAW);
						
			glBindVertexArray(0);			
		}		
	}

	Mesh::~Mesh()
	{
		// Se liberan los VBOs usados:
		glDeleteVertexArrays(1, &vao_id);
		glDeleteBuffers(VBO_COUNT, vbo_ids);
	}

	void Mesh::update(float angle_aux, float scale_aux, float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z)
	{
		angle += angle_aux;
		position = glm::vec3(pos_x, pos_y, pos_z);
		rotation = glm::vec3(rot_x, rot_y, rot_z);
		scale = glm::vec3(scale_aux, scale_aux, scale_aux);

		//Actualiza cada hijo
		for (auto & child : children)
		{
			child->update(angle_aux, scale_aux, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z);
		}
	}

	void Mesh::add(shared_ptr<Mesh > & m) {
		children.push_back(m);
	}

	void Mesh::render(glm::mat4 model_view_matrix_parent)
	{		
		if (render_b)
		{
			//Activa el shader
			material->use();

			// Matriz de transformacion en funcion de la de su padre 
			glm::mat4 model_view_matrix = model_view_matrix_parent;

			// Se rota la mesh y se mueve a la posicion introducida por parametros:
			model_view_matrix = glm::translate(model_view_matrix, position);
			model_view_matrix = glm::rotate(model_view_matrix, angle, rotation);
			model_view_matrix = glm::scale(model_view_matrix, scale);
			glUniformMatrix4fv(material->get_model_view_id(), 1, GL_FALSE, glm::value_ptr(model_view_matrix));

			//Matriz de normales
			glm::mat4 normal_matrix = glm::transpose(glm::inverse(model_view_matrix));
			glUniformMatrix4fv(material->get_normal_matrix_id(), 1, GL_FALSE, glm::value_ptr(normal_matrix));

			glBindVertexArray(vao_id);
			glDrawElements(GL_TRIANGLES, original_indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			//Actualiza cada hijo
			for (auto & child : children)
			{
				child->render(model_view_matrix);
			}
		}
	}	

}
