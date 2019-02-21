
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  SEEKABLE                                                                   *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_SEEKABLE_HEADER
#define TOOLKIT_SEEKABLE_HEADER

    #include "types.hpp"

    namespace toolkit
    {

        class Seekable
        {
        public:

            virtual ~Seekable()
            {
            }

        public:

            virtual bool     seek (uint64_t location) = 0;
            virtual uint64_t tell () = 0;

        };

    }

#endif
