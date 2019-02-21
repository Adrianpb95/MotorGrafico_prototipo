
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Copyright © 2014+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cassert>
#include <fstream>
#include "Shader.hpp"

namespace example
{

    Shader::Source_Code Shader::Source_Code::from_file (const std::string & file_path)
    {
        Source_Code source_code;

        // Se abre el archivo:

        using std::fstream;

        fstream file_reader(file_path, fstream::in | fstream::binary);

        if (file_reader.is_open ())
        {
            // Se determina el tamaño del archivo:

            file_reader.seekg (0, fstream::end);

            size_t file_size = size_t(file_reader.tellg ());

            if (file_reader.good () && file_size > 0)
            {
                // Se lee el contenido del archivo en una cadena:
                // Se espera que el archivo contenga un byte por cada carácter con código menor que 128 (UTF-8, etc.).

                source_code.string.resize (file_size);

                file_reader.seekg (0, fstream::beg);

                file_reader.read  (&source_code.string.front (), file_size);

                assert(file_reader.good ());
            }
        }
        else
            assert(false);

        return (source_code);
    }

    Shader::Shader(const Source_Code & source_code, GLenum shader_type)
    :
        shader_object_id(0)
    {
        if (source_code.is_not_empty ())
        {
            // Se crea el shader object:

            shader_object_id = glCreateShader (shader_type);

            // Se carga el código del shader:

            const char * shader_code_list[] = {        source_code         };
            const GLint  shader_size_list[] = { (GLint)source_code.size () };

            glShaderSource  (shader_object_id, 1, shader_code_list, shader_size_list);

            // Se compila el shader:

            glCompileShader (shader_object_id);

            // Se comprueba si la compilación ha tenido éxito:

            GLint succeeded = GL_FALSE;

            glGetShaderiv (shader_object_id, GL_COMPILE_STATUS, &succeeded);

            if (!succeeded)
            {
                // Se guarda el log del error que ha ocurrido:

                GLint log_length;

                glGetShaderiv (shader_object_id, GL_INFO_LOG_LENGTH, &log_length);

                if (log_length > 0)
                {
                    log_string.resize  (log_length);

                    glGetShaderInfoLog (shader_object_id, log_length, NULL, &log_string.front ());
                }

                // Se libera el shader object, ya que ahora es un recurso encapsulado no usable:

                glDeleteShader (shader_object_id);

                shader_object_id = 0;

                assert(false);
            }
        }
        else
            assert(false);
    }

    Shader::~Shader()
    {
        // Borrar un shader object cuando se ha añadido a un program object no tiene efectos adversos:

        glDeleteShader (shader_object_id);

        shader_object_id = 0;
    }

}
