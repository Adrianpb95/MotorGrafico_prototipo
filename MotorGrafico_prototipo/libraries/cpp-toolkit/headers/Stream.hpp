
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  STREAM                                                                     *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_STREAM_HEADER
#define TOOLKIT_STREAM_HEADER

    #include "types.hpp"
    #include "Seekable.hpp"
    #include "Cloneable.hpp"

    namespace toolkit
    {

        template< class STREAM_TYPE >
        class Stream
        {
        public:

            virtual ~Stream()
            {
            }

        public:

            Seekable * seekable ()
            {
                return (dynamic_cast< Seekable * >(this));
            }

            const Seekable * seekable () const
            {
                return (dynamic_cast< const Seekable * >(this));
            }

            Cloneable< STREAM_TYPE > * cloneable ()
            {
                return (dynamic_cast< Cloneable< STREAM_TYPE > * >(this));
            }

            const Cloneable< STREAM_TYPE > * cloneable () const
            {
                return (dynamic_cast< const Cloneable< STREAM_TYPE > * >(this));
            }

        public:

            bool is_seekable () const
            {
                return (seekable ());
            }

            bool is_not_seekable () const
            {
                return (not seekable ());
            }

            bool is_cloneable () const
            {
                return (cloneable ());
            }

            bool is_not_cloneable () const
            {
                return (not cloneable ());
            }

        public:

            virtual bool good () const = 0;
            virtual bool fail () const = 0;
            virtual bool eos  () const = 0;
            // AÑADIR EL MÉTODO BOOL BAD();

        };

    }

#endif
