
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

#ifndef OGL_SHADER_PROGRAM_HEADER
#define OGL_SHADER_PROGRAM_HEADER

    #include <cassert>
    #include "Shader.hpp"
    #include <Vector.hpp>
    #include <Matrix.hpp>

    namespace example
    {

        using toolkit::Vector2f;
        using toolkit::Vector3f;
        using toolkit::Vector4f;
        using toolkit::Matrix22f;
        using toolkit::Matrix33f;
        using toolkit::Matrix44f;

        class Shader_Program : Non_Copyable
        {
        public:

            static void disable ()
            {
                glUseProgram (0);
            }

        private:

            GLuint      program_object_id;
            bool        link_completed;
            std::string log_string;

        public:

            Shader_Program()
            {
                program_object_id = glCreateProgram ();
                link_completed    = false;

                assert(program_object_id != 0);
            }

           ~Shader_Program()
            {
                glDeleteProgram (program_object_id);

                program_object_id = 0;
            }

        public:

            bool is_usable () const
            {
                return (link_completed);
            }

        public:

            void attach (const Shader & shader)
            {
                glAttachShader (program_object_id, shader);
            }

            void detach (const Shader & shader)
            {
                glDetachShader (program_object_id, shader);
            }

        public:

            bool link ();

            void use () const
            {
                assert(is_usable ());

                glUseProgram (program_object_id);
            }

        public:

            GLint get_uniform_id (const char * identifier)
            {
                assert (is_usable ());

                GLint   uniform_id  = glGetUniformLocation (program_object_id, identifier);

                assert (uniform_id != -1);

                return (uniform_id);
            }

            void set_uniform_value (GLint uniform_id, const GLint     & value ) { glUniform1i (uniform_id, value); }
            void set_uniform_value (GLint uniform_id, const float     & value ) { glUniform1f (uniform_id, value); }
            void set_uniform_value (GLint uniform_id, const Vector2f  & vector) { glUniform2f (uniform_id, vector[0], vector[1]); }
            void set_uniform_value (GLint uniform_id, const Vector3f  & vector) { glUniform3f (uniform_id, vector[0], vector[1], vector[2]); }
            void set_uniform_value (GLint uniform_id, const Vector4f  & vector) { glUniform4f (uniform_id, vector[0], vector[1], vector[2], vector[3]); }
            void set_uniform_value (GLint uniform_id, const Matrix22f & matrix) { glUniformMatrix2fv (uniform_id, 1, GL_FALSE, matrix.values); }
            void set_uniform_value (GLint uniform_id, const Matrix33f & matrix) { glUniformMatrix3fv (uniform_id, 1, GL_FALSE, matrix.values); }
            void set_uniform_value (GLint uniform_id, const Matrix44f & matrix) { glUniformMatrix4fv (uniform_id, 1, GL_FALSE, matrix.values); }

        public:

            GLint get_vertex_attribute_id (const char * identifier)
            {
                assert (is_usable ());

                GLint   attribute_id  = glGetAttribLocation (program_object_id, identifier);

                assert (attribute_id != -1);

                return (attribute_id);
            }

            void set_vertex_attribute (GLint attribute_id, const float    & value ) { glVertexAttrib1f  (attribute_id,  value    ); }
            void set_vertex_attribute (GLint attribute_id, const Vector2f & vector) { glVertexAttrib2fv (attribute_id, &vector[0]); }
            void set_vertex_attribute (GLint attribute_id, const Vector3f & vector) { glVertexAttrib3fv (attribute_id, &vector[0]); }
            void set_vertex_attribute (GLint attribute_id, const Vector4f & vector) { glVertexAttrib4fv (attribute_id, &vector[0]); }

        public:

            const std::string & log () const
            {
                return (log_string);
            }

        public:

            operator GLuint () const
            {
                return (program_object_id);
            }

        };

    }

#endif
