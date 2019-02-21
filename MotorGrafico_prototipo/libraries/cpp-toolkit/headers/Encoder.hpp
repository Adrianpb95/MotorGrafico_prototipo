
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  ENCODER                                                                    *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_ENCODER_HEADER
#define TOOLKIT_ENCODER_HEADER

    #include "Shared_Ptr.hpp"
    #include "Output_Stream.hpp"

    namespace toolkit
    {

        class Encoder : public Output_Stream
        {
        protected:

            Output_Stream             & destination;
            Shared_Ptr< Output_Stream > destination_pointer;

        public:

            Encoder(Output_Stream & given_destination)
            :
                destination(given_destination)
            {
            }

            Encoder(const Shared_Ptr< Output_Stream > & given_destination)
            :
                destination        (*given_destination),
                destination_pointer( given_destination)
            {
            }

            virtual ~Encoder()
            {
            }

        };

    }

#endif
