
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  VOID ENCODER                                                               *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_VOID_ENCODER_HEADER
#define TOOLKIT_VOID_ENCODER_HEADER

    #include "Encoder.hpp"

    namespace toolkit
    {

        class Void_Encoder : public Encoder
        {
        public:

            Void_Encoder(Output_Stream & given_destination)
            :
                Encoder(given_destination)
            {
            }

        public:

            bool write (const byte * buffer, size_t size)
            {
                return (destination.write (buffer, size));
            }

            bool put (byte value)
            {
                return (destination.put (value));
            }

            bool good () const { return (destination.good ()); }
            bool fail () const { return (destination.fail ()); }
            bool eos  () const { return (destination.eos  ()); }

        public:

            using Output_Stream::put;

        };

    }

#endif
