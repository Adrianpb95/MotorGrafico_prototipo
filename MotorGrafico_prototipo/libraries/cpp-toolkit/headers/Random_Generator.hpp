
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  RANDOM GENERATOR                                                           *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_RANDOM_GENERATOR_HEADER
#define TOOLKIT_RANDOM_GENERATOR_HEADER

    #include "types.hpp"

    namespace toolkit
    {

        class Random_Generator
        {
        private:

            uint32_t x;
            uint32_t seed;

        public:

            Random_Generator()
            {
                int value = 0;
                x     = 2463534242u;
                seed  = uint32_t((value ^ x) * x);
            }

            Random_Generator(int32_t value)
            {
                x    = 2463534242u;
                seed = uint32_t((value ^ x) * x);
            }

            int next_int ()
            {
                return static_cast< int >(next_uint32 ());
            }

            unsigned int next_uint ()
            {
                return static_cast< unsigned int >(next_uint32 ());
            }

            uint32_t next_uint32 ()
            {
                x ^= x << 13;
                x ^= x >> 17;

                return (seed = (x ^= x << 5) ^ seed);
            }

        };

    }

#endif
