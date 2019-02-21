
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  VOID DECODER                                                               *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_VOID_DECODER_HEADER
#define TOOLKIT_VOID_DECODER_HEADER

    #include "Decoder.hpp"

    namespace toolkit
    {

        class Void_Decoder : public Decoder
        {
        public:

            Void_Decoder(Input_Stream & given_source)
            :
                Decoder(given_source)
            {
            }

        public:

            uint64_t read (byte * buffer, size_t size)
            {
                return (source.read (buffer, size));
            }

            byte get  ()
            {
                return (source.get  ());
            }

            bool good () const
            {
                return (source.good ());
            }

            bool fail () const
            {
                return (source.fail ());
            }

            bool eos  () const
            {
                return (source.eos  ());
            }

        public:

            using Input_Stream::get;

        };

    }

#endif
