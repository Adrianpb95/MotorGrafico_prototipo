
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  POINTER                                                                    *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_POINTER_HEADER
#define TOOLKIT_POINTER_HEADER

    #include <cassert>
    #include "types.hpp"

    namespace toolkit
    {

        template< typename TYPE > class Shared_Ptr;

        template< typename TYPE = void >
        class Pointer
        {
        public:

            typedef TYPE element_type;

        private:

            element_type * address;

        public:

            Pointer()
            {
                address = 0;
            }

            Pointer(Null)
            {
                address = 0;
            }

        public:

            Pointer(element_type * given_address)
            {
                address = given_address;
            }

            Pointer(const Pointer & other)
            {
                this->address = other.address;
            }

            Pointer(const Shared_Ptr< TYPE > & shared_pointer)
            {
                address = shared_pointer.get ();
            }

        public:

            template< typename RELATED_TYPE >
            Pointer(RELATED_TYPE * given_value)
            {
                address = static_cast< RELATED_TYPE * >(given_value);
            }

            template< typename RELATED_TYPE >
            Pointer(const Pointer< RELATED_TYPE > & pointer)
            {
                address = static_cast< RELATED_TYPE * >(pointer.get ());
            }

            template< typename RELATED_TYPE >
            Pointer(const Shared_Ptr< RELATED_TYPE > & shared_pointer)
            {
                address = static_cast< RELATED_TYPE * >(shared_pointer.get ());
            }

        public:

            element_type * get () const
            {
                return (address);
            }

            bool is_null () const
            {
                return (address == 0);
            }

            bool is_not_null () const
            {
                return (address != 0);
            }

        public:

            element_type & operator  * () const
            {
                assert (address != 0);
                return *address;
            }

            element_type * operator -> () const
            {
                assert (address != 0);
                return (address);
            }

            operator element_type * () const
            {
                return (address);
            }

        public:

            bool operator == (const Pointer & other) const
            {
                return (this->address == other.address);
            }

            bool operator != (const Pointer & other) const
            {
                return (this->address != other.address);
            }

        };

        template< >
        class Pointer< void >
        {
        public:

            typedef void element_type;

        private:

            element_type * address;

        public:

            Pointer()
            {
                address = 0;
            }

            Pointer(Null)
            {
                address = 0;
            }

        public:

            Pointer(element_type  * given_address)
            {
                address = given_address;
            }

            Pointer(const Pointer & other)
            {
                this->address = other.address;
            }

        public:

            template< typename ANY_TYPE >
            Pointer(ANY_TYPE * given_value)
            {
                address = given_value;
            }

            template< typename ANY_TYPE >
            Pointer(const Pointer< ANY_TYPE > & pointer)
            {
                address = pointer.get ();
            }

        public:

            element_type * get () const
            {
                return (address);
            }

            bool is_null () const
            {
                return (address == 0);
            }

            bool is_not_null () const
            {
                return (address != 0);
            }

        public:

            operator element_type * () const
            {
                return (address);
            }

            operator bool () const
            {
                return (address != 0);
            }

        public:

            bool operator == (const Pointer & other) const
            {
                return (this->address == other.address);
            }

            bool operator != (const Pointer & other) const
            {
                return (this->address != other.address);
            }

        };

    }

#endif
