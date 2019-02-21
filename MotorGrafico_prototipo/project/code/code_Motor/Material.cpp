/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Material.hpp"
#include "Color_Buffer_Rgba8888.hpp"

namespace example
{
	Material::Material(const char * path)
		:
		has_texture(false),
		texture(load_texture(path))
	{
		// Se compilan y linkan los shaders:
		shader_program.attach(Vertex_Shader(Shader::Source_Code::from_string(vertex_shader_code)));
		shader_program.attach(Fragment_Shader(Shader::Source_Code::from_string(fragment_shader_code)));

		shader_program.link();

		model_view_matrix_id = shader_program.get_uniform_id("model_view_matrix");
		projection_matrix_id = shader_program.get_uniform_id("projection_matrix");
		normal_matrix_id	 = shader_program.get_uniform_id("normal_matrix");

		

		if (path != 0)
		{
			has_texture = texture.get() != 0;

			if (has_texture)
			{
				// Se habilitan las texturas, se genera un id para un búfer de textura,
				// se selecciona el búfer de textura creado y se configuran algunos de
				// sus parámetros:

				glEnable(GL_TEXTURE_2D);
				glGenTextures(1, &texture_id);
				glBindTexture(GL_TEXTURE_2D, texture_id);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				// Se suben los colores de la textura a la memoria de vídeo:

				glTexImage2D
				(
					GL_TEXTURE_2D,
					0,
					GL_RGBA,
					texture->get_width(),
					texture->get_height(),
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					texture->colors()
				);
			}
			else
				assert(false);
		}
		else
			assert(false);		
	}


	Material::~Material()
	{
		if (has_texture)
		{
			glDeleteTextures(1, &texture_id);
		}
	}

	void Material::configure_light()
	{
		GLint light_position = shader_program.get_uniform_id("light.position");
		glUniform4f(light_position, 0.0f, 5.0f, 10.0f, 1.0f);
		GLint ambient_intensity = shader_program.get_uniform_id("light.ambient_intensity");
		glUniform1f(ambient_intensity, 0.2f);
		GLint diffuse_intensity = shader_program.get_uniform_id("light.diffuse_intensity");
		glUniform1f(diffuse_intensity, 0.8f);
		GLint light_color = shader_program.get_uniform_id("light.color");
		glUniform3f(light_color, 1.0f, 1.0f, 1.0f);
	}

	std::shared_ptr< Texture > Material::load_texture(const char * texture_file_path)
	{
		std::shared_ptr< Texture > texture;
		tga_image				   loaded_image;

		if (tga_read(&loaded_image, texture_file_path) == TGA_NOERR)
		{
			// Si se ha podido cargar la imagen desde el archivo, se crea un búfer para una textura:

			texture.reset(new Texture(loaded_image.width, loaded_image.height));

			// Se convierte el formato de píxel de la imagen cargada a RGBA8888:

			tga_convert_depth(&loaded_image, texture->bits_per_color());
			tga_swap_red_blue(&loaded_image);

			// Se copian los pixels del búfer de la imagen cargada al búfer de la textura:

			Texture::Color * loaded_image_pixels = reinterpret_cast< Texture::Color * >(loaded_image.image_data);
			Texture::Color * loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
			Texture::Color * image_buffer_pixels = texture->colors();

			while (loaded_image_pixels < loaded_image_pixels_end)
			{
				*image_buffer_pixels++ = *loaded_image_pixels++;
			}

			tga_free_buffers(&loaded_image);
		}

		return (texture);
	}


}