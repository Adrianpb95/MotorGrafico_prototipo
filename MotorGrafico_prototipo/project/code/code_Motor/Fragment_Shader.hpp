
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

#ifndef OGL_FRAGMENT_SHADER_HEADER
#define OGL_FRAGMENT_SHADER_HEADER

    #include "Shader.hpp"

    namespace example
    {

        class Fragment_Shader : public Shader
        {
        public:

            Fragment_Shader(const Source_Code & source_code)
            :
                Shader(source_code, GL_FRAGMENT_SHADER)
            {
            }
        };
    }

#endif
