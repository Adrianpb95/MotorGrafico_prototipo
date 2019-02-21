
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  OBFUSCATION ENCODER                                                        *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_OBFUSCATION_ENCODER_HEADER
#define TOOLKIT_OBFUSCATION_ENCODER_HEADER

    #include <vector>
    #include "Encoder.hpp"
    #include "Random_Generator.hpp"

    namespace toolkit
    {

        class Obfuscation_Encoder : public Encoder
        {
        private:

            Random_Generator    random_generator;
            uint32_t            last_output;
            std::vector< byte > buffer;

        public:

            Obfuscation_Encoder(Output_Stream & given_destination, int32_t key)
            :
                Encoder(given_destination),
                random_generator(uint32_t(key)),
                last_output(0xAA)
            {
            }

            Obfuscation_Encoder(const Shared_Ptr< Output_Stream > & given_destination, int32_t key)
            :
                Encoder(given_destination),
                random_generator(uint32_t(key)),
                last_output(0xAA)
            {
            }

        public:

            bool write (const byte * input_buffer, size_t size)
            {
                if (size > buffer.size ())
                {
                    buffer.resize (size);
                }

                const byte * input  = input_buffer;
                      byte * output = &buffer.front ();

                for (const byte * input_end = input_buffer + size; input < input_end; input++, output++)
                {
                    *output = byte(last_output = uint32_t(*input) ^ last_output ^ random_generator.next_uint32 ());
                }

                return (destination.write (&buffer.front (), size));
            }

            bool put (byte value)
            {
                return (destination.put (byte(last_output = uint32_t(value) ^ last_output ^ random_generator.next_uint32 ())));
            }

            bool good () const { return (destination.good ()); }
            bool fail () const { return (destination.fail ()); }
            bool eos  () const { return (destination.eos  ()); }

        public:

            using Output_Stream::put;

        };

    }

#endif
