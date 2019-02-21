
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  NON COPYABLE                                                               *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_NON_COPYABLE_HEADER
#define TOOLKIT_NON_COPYABLE_HEADER

    namespace toolkit
    {

        class Non_Copyable
        {
        protected:

            Non_Copyable() { }
            virtual ~Non_Copyable() { }

        private:

            Non_Copyable(const Non_Copyable & );
            Non_Copyable & operator = (const Non_Copyable & );

        };

    }

    typedef toolkit::Non_Copyable Non_Copyable;

#endif
