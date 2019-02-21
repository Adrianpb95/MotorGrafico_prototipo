
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

#include "Shader_Program.hpp"

namespace example
{

    bool Shader_Program::link ()
    {
        glLinkProgram (program_object_id);

        // Se comprueba si el linkage ha tenido éxito:

        GLint succeeded = GL_FALSE;

        glGetProgramiv (program_object_id, GL_LINK_STATUS, &succeeded);

        if (!succeeded)
        {
            // Se guarda el log del error que ha ocurrido:

            GLint log_length;

            glGetShaderiv (program_object_id, GL_INFO_LOG_LENGTH, &log_length);

            if (log_length > 0)
            {
                log_string.resize  (log_length);

                glGetShaderInfoLog (program_object_id, log_length, NULL, &log_string.front ());
            }

            assert(false);
        }

        return (link_completed = (succeeded != GL_FALSE));
    }

}
