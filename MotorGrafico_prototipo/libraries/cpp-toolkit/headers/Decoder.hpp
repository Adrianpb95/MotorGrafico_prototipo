
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  DECODER                                                                    *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_DECODER_HEADER
#define TOOLKIT_DECODER_HEADER

    #include "Shared_Ptr.hpp"
    #include "Input_Stream.hpp"

    namespace toolkit
    {

        class Decoder : public Input_Stream
        {
        protected:

            Input_Stream             & source;
            Shared_Ptr< Input_Stream > source_pointer;

        public:

            Decoder(Input_Stream & given_source)
            :
                source(given_source)
            {
            }

            Decoder(const Shared_Ptr< Input_Stream > & given_source)
            :
                source        (*given_source),
                source_pointer( given_source)
            {
            }

            virtual ~Decoder()
            {
            }

        };

    }

#endif
