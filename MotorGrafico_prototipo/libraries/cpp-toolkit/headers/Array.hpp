
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  ARRAY                                                                      *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_ARRAY_HEADER
#define TOOLKIT_ARRAY_HEADER

    #include <cassert>
    #include <stdexcept>
    #include <algorithm>

    namespace toolkit
    {

        template< typename TYPE, size_t SIZE >
        class Array
        {
        public:

            typedef       TYPE          value_type;
            typedef       value_type  & reference;
            typedef const value_type  & const_reference;
            typedef       value_type  * pointer;
            typedef const value_type  * const_pointer;
            typedef       pointer       iterator;
            typedef       const_pointer const_iterator;
            typedef       size_t        size_type;
            typedef       ptrdiff_t     difference_type;

        private:

            value_type elements[SIZE];

        public:

            size_type size () const
            {
                return (SIZE);
            }

            bool empty () const
            {
                return (SIZE == 0);
            }

            pointer data ()
            {
                return (elements);
            }

            const_pointer data () const
            {
                return (elements);
            }

        public:

            iterator begin ()
            {
                return (elements);
            }

            const_iterator begin () const
            {
                return (elements);
            }

            const_iterator cbegin () const
            {
                return (elements);
            }

            iterator end ()
            {
                return (elements + SIZE);
            }

            const_iterator end () const
            {
                return (elements + SIZE);
            }

            const_iterator cend () const
            {
                return (elements + SIZE);
            }

            reference front ()
            {
                return (elements[0]);
            }

            const_reference front () const
            {
                return (elements[0]);
            }

            reference back ()
            {
                return (elements[SIZE - 1]);
            }

            const_reference back () const
            {
                return (elements[SIZE - 1]);
            }

            reference at (size_type index)
            {
                if (index >= SIZE)
                {
                    throw std::out_of_range();
                }

                return (elements[index]);
            }

            const_reference at (size_type index) const
            {
                return (const_cast< Array * >(this)->at (index));
            }

        public:

            reference operator [] (size_type index)
            {
                assert (index < SIZE);
                return (elements[index]);
            }

            const_reference operator [] (size_type index) const
            {
                assert (index < SIZE);
                return (elements[index]);
            }

        public:

            Array & operator = (const Array< TYPE, SIZE > & other)
            {
                if (this != &other)
                {
                    std::copy (other.begin (), other.end (), this->begin ());
                }

                return (*this);
            }

            void swap (Array< TYPE, SIZE > & other)
            {
                std::swap_ranges (this->begin (), this->end (), other.begin ());
            }

        };

    }

#endif
