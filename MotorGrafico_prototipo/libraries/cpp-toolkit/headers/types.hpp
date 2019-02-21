
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  TYPES                                                                      *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_TYPES_HEADER
#define TOOLKIT_TYPES_HEADER

    #include "macros.hpp"
    #include  TOOLKIT_STDINT_HEADER

    typedef unsigned char byte;

    class Null
    {
    public:

        operator void * () const
        {
            return (0);
        }

        template< typename TYPE >
        operator TYPE * () const
        {
            return (0);
        }

        template< class CLASS, typename TYPE >
        operator TYPE CLASS::* () const
        {
            return (0);
        }

    private:

        void operator & () const;

    };

    const Null null = { };

#endif
