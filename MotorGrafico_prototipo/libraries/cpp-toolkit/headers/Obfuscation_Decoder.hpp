
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  OBFUSCATION DECODER                                                        *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_OBFUSCATION_DECODER_HEADER
#define TOOLKIT_OBFUSCATION_DECODER_HEADER

    #include "Decoder.hpp"
    #include "Random_Generator.hpp"

    namespace toolkit
    {

        class Obfuscation_Decoder : public Decoder
        {
        private:

            Random_Generator random_generator;
            uint32_t         last_input;

        public:

            Obfuscation_Decoder(Input_Stream & given_source, int32_t key)
            :
                Decoder(given_source),
                random_generator(uint32_t(key)),
                last_input(0xAA)
            {
            }

            Obfuscation_Decoder(const Shared_Ptr< Input_Stream > & given_source, int32_t key)
            :
                Decoder(given_source),
                random_generator(uint32_t(key)),
                last_input(0xAA)
            {
            }

        public:

            uint64_t read (byte * buffer, size_t size)
            {
                uint64_t got_size = source.read (buffer, size);

                for (byte * iterator = buffer, * end = buffer + got_size; iterator != end; iterator++)
                {
                    uint32_t input = *iterator;

                   *iterator   = byte(input ^ last_input ^ random_generator.next_uint32 ());

                    last_input = input;
                }

                return (got_size);
            }

            byte get ()
            {
                uint32_t input  = source.get ();
                uint32_t output = input ^ last_input ^ random_generator.next_uint32 ();

                last_input = input;

                return byte(output);
            }

            bool good () const { return (source.good ()); }
            bool fail () const { return (source.fail ()); }
            bool eos  () const { return (source.eos  ()); }

        public:

            using Input_Stream::get;

        };

    }

#endif
