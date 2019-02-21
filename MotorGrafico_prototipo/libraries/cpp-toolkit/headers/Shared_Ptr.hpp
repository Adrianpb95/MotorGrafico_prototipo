
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  SHARED PTR                                                                 *
 *                                                                             *
 *  Copyright © 2011+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_SHARED_PTR_HEADER
#define TOOLKIT_SHARED_PTR_HEADER

    #include <memory>
    #include <cassert>
    #include "types.hpp"

    namespace toolkit
    {

        template< typename TYPE >
        class Shared_Ptr
        {
            template< typename ANY_TYPE > friend class Shared_Ptr;

        public:

            typedef TYPE   element_type;
            typedef size_t counter_type;

        private:

            element_type * address;
            counter_type * counter;

        public:

            Shared_Ptr()
            {
                clear ();
            }

            Shared_Ptr(Null)
            {
                clear ();
            }

            explicit Shared_Ptr(element_type * given_address)
            :
                address(given_address),
                counter(new counter_type(1))
            {
            }

            Shared_Ptr(const Shared_Ptr & other)
            {
                hold (other.address, other.counter);
            }

        public:

            explicit Shared_Ptr(std::auto_ptr< element_type > other_address)
            :
                address(other_address.release ()),
                counter(new counter_type(1))
            {
            }

        public:

            template< typename  RELATED_TYPE >
            explicit Shared_Ptr(RELATED_TYPE * given_address)
            :
                address(given_address),
                counter(new counter_type(1))
            {
            }

            template< typename RELATED_TYPE >
            Shared_Ptr(const Shared_Ptr< RELATED_TYPE > & other)
            {
                hold (other.address, other.counter);
            }

            template< typename  RELATED_TYPE >
            explicit Shared_Ptr(std::auto_ptr< RELATED_TYPE > pointer)
            :
                address(pointer.release ( )),
                counter(new counter_type(1))
            {
            }

        public:

           ~Shared_Ptr()
            {
                reset ();
            }

        public:

            element_type * get () const
            {
                return (address);
            }

            size_t use_count () const
            {
                return (counter ?  *counter :  0);
            }

            bool unique () const
            {
                return (counter && *counter == 1);
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

            void reset ()
            {
                release ();
                clear   ();
            }

            template< typename RELATED_TYPE >
            void reset (RELATED_TYPE * new_address)
            {
                release ();

                if (new_address == 0)
                {
                    clear ();
                }
                else
                {
                    address = new_address;
                    counter = new counter_type(1);
                }
            }

        public:

            Shared_Ptr & operator = (const Shared_Ptr & other)
            {
                if (other.address == 0)
                {
                    reset ();
                }
                else
                if (other.address != this->address)
                {
                    release ();

                    this->address  = other.address;
                  *(this->counter  = other.counter) += 1;
                }

                return (*this);
            }

            template< typename RELATED_TYPE >
            Shared_Ptr & operator = (const Shared_Ptr< RELATED_TYPE > & other)
            {
                if (other.address == 0)
                {
                    reset ();
                }
                else
                if (other.address != this->address)
                {
                    release ();

                    this->address  = other.address;
                  *(this->counter  = other.counter) += 1;
                }

                return (*this);
            }

        public:

            TYPE & operator *  () const
            {
                assert (address);
                return *address;
            }

            TYPE * operator -> () const
            {
                assert (address);
                return (address);
            }

            operator bool () const
            {
                return (address != 0);
            }

        public:

            template< typename RELATED_TYPE >
            bool operator == (const Shared_Ptr< RELATED_TYPE > & other) const
            {
                return (this->address == other.address);
            }

            template< typename RELATED_TYPE >
            bool operator != (const Shared_Ptr< RELATED_TYPE > & other) const
            {
                return (this->address != other.address);
            }

        private:

            void hold (element_type * new_address, counter_type * new_counter)
            {
                address = new_address;
                counter = new_counter;

                if (new_address != 0)
                {
                    ++(*counter);
                }
            }

            void release ()
            {
                if (counter && --(*counter) == 0)
                {
                    delete address;
                    delete counter;
                }
            }

            void clear ()
            {
                address = 0;
                counter = 0;
            }

        };

    }

#endif
