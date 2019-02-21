
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  CLONEABLE                                                                  *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_CLONEABLE_HEADER
#define TOOLKIT_CLONEABLE_HEADER

    #include <Shared_Ptr.hpp>

    namespace toolkit
    {

        template< class TYPE >
        class Cloneable
        {
        public:

            virtual ~Cloneable()
            {
            }

        public:

            virtual Shared_Ptr< TYPE > clone () const = 0;

        };

    }

#endif
