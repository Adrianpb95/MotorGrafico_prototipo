
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  STRING                                                                     *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_STRING_HEADER
#define TOOLKIT_STRING_HEADER

    #include <string>
    #include <cstring>
    #include "Char.hpp"
    #include <algorithm>
    #include "Shared_Ptr.hpp"

    class QChar;
    class QString;

    namespace toolkit
    {

        class String
        {
        public:

            typedef       Char          value_type;
            typedef       Char        * pointer;
            typedef const Char        * const_pointer;
            typedef       Char        & reference;
            typedef const Char        & const_reference;
            typedef       pointer       iterator;
            typedef       const_pointer const_iterator;

        private:

            template< typename CHAR_TYPE >
            class Buffer
            {
            private:

                static const size_t default_capacity = 32;
                static const size_t cushion_capacity = 64;

            public:

                value_type static_chars[default_capacity];
                pointer    dynamic_chars;
                pointer    characters;

                size_t     size_value;
                size_t     capacity_value;

            public:

                Buffer()
                {
                    size_value     = 0;
                    characters     = static_chars;
                    dynamic_chars  = null;
                    capacity_value = default_capacity;
                }

                Buffer(size_t initial_size)
                {
                    dynamic_chars = null;

                    if (initial_size > default_capacity)
                    {
                        capacity_value = size_value = 0;

                        reserve (initial_size);
                    }
                    else
                    {
                        characters     = static_chars;
                        capacity_value = default_capacity;
                    }

                    size_value = initial_size;
                }

               ~Buffer()
                {
                    deallocate ();
                }

            public:

                size_t size () const
                {
                    return (size_value);
                }

                size_t capacity () const
                {
                    return (capacity_value);
                }

                bool empty () const
                {
                    return (size_value == 0);
                }

                void resize (size_t new_size)
                {
                    if (new_size > capacity_value)
                    {
                        reserve (new_size);
                    }

                    size_value = new_size;
                }

                void enlarge (size_t enlargement_size)
                {
                    resize (size_value + enlargement_size);
                }

                void reserve (size_t new_capacity)
                {
                    if (new_capacity > capacity_value)
                    {
                        pointer new_buffer = new value_type[capacity_value = new_capacity + cushion_capacity];

                        if (size_value > 0)
                        {
                            std::copy (characters, characters + size_value, new_buffer);
                        }

                        deallocate ();

                        characters = dynamic_chars = new_buffer;
                    }
                }

                void clear ()
                {
                    size_value = 0;
                }

            public:

                iterator begin ()
                {
                    return (characters);
                }

                const_iterator begin () const
                {
                    return (characters);
                }

                iterator end ()
                {
                    return (characters + size_value);
                }

                const_iterator end () const
                {
                    return (characters + capacity);
                }

            private:

                void deallocate ()
                {
                    if (dynamic_chars) delete [] dynamic_chars;
                }

            };

            typedef Buffer< value_type >  Char_Buffer;
            typedef Buffer< char       >  char_buffer;
            typedef Buffer< wchar_t    > wchar_buffer;

        public:

            static const size_t npos = ~size_t(0);

        private:

            Shared_Ptr< Char_Buffer > characters;

        public:

            String()
            :
                characters(new Char_Buffer)
            {
            }

            String(const String & other)
            :
                characters(other.characters)
            {
            }

            String(const std::string & source)
            :
                characters(new Char_Buffer(source.size ()))
            {
                if (not source.empty ())
                {
                    std::copy (source.begin (), source.end (), begin ());
                }
            }

            String(const std::wstring & source)
            :
                characters(new Char_Buffer(source.size ()))
            {
                if (not source.empty ())
                {
                    std::copy (source.begin (), source.end (), begin ());
                }
            }

            String(const QString & source);

            String(signed int initial_size)
            :
                characters(new Char_Buffer(size_t(initial_size)))
            {
            }

            String(unsigned int initial_size)
            :
                characters(new Char_Buffer(size_t(initial_size)))
            {
            }

            String(const char & character)
            :
                characters(new Char_Buffer(1))
            {
                front () = character;
            }

            String(const wchar_t & character)
            :
                characters(new Char_Buffer(1))
            {
                front () = character;
            }

            String(const QChar & character);

            String(const char * const cstring)
            :
                characters(new Char_Buffer(std::strlen (cstring)))
            {
                std::copy (cstring, cstring + size (), begin ());
            }

            String(const wchar_t * const wcstring)
            :
                characters(new Char_Buffer(std::wcslen (wcstring)))
            {
                std::copy (wcstring, wcstring + size (), begin ());
            }

        public:

            size_t size () const
            {
                return (characters->size ());
            }

            size_t length () const
            {
                return (characters->size ());
            }

            size_t capacity () const
            {
                return (characters->capacity ());
            }

            bool empty () const
            {
                return (characters->empty ());
            }

            void resize (size_t new_size)
            {
                if (sharing ())
                {
                    make_copy ();
                }

                characters->resize (new_size);
            }

            void reserve (size_t new_capacity)
            {
                characters->reserve (new_capacity);
            }

            void clear ()
            {
                if (sharing ())
                {
                    characters.reset (new Char_Buffer);
                }
                else
                {
                    characters->clear ();
                }
            }

        public:

            iterator begin ()
            {
                if (sharing ())
                {
                    make_copy ();
                }

                return (characters->begin ());
            }

            const_iterator begin () const
            {
                return (characters->begin ());
            }

            iterator end ()
            {
                if (sharing ())
                {
                    make_copy ();
                }

                return (characters->end ());
            }

            const_iterator end () const
            {
                return (characters->end ());
            }

            reference front ()
            {
                if (sharing ())
                {
                    make_copy ();
                }

                return (*begin ());
            }

            const_reference front () const
            {
                return (*begin ());
            }

            reference back ()
            {
                if (sharing ())
                {
                    make_copy ();
                }

                return (*(end () - 1));
            }

            const_reference back () const
            {
                return (*(end () - 1));
            }

            value_type & at (size_t index)
            {
                return (this->operator [] (index));
            }

            const value_type & at (size_t index) const
            {
                return (this->operator [] (index));
            }

        public:

            String & assign (const value_type & character)
            {
                characters.reset (new Char_Buffer(1));

                front () = character;

                return (*this);
            }

            String & assign (const String & other)
            {
                if (this->characters != other.characters)
                {
                    this->characters  = other.characters;
                }

                return (*this);
            }

            String & append (const char & character)
            {
                return (append (value_type(character)));
            }

            String & append (const wchar_t & character)
            {
                return (append (value_type(character)));
            }

            String & append (const value_type & character);
            String & append (const String     & other    );
            String & append (const char       * cstring  );
            String & append (const wchar_t    * wcstring );

            void     swap   (String & other);

        public:

            void push_back (const value_type & character)
            {
                append (character);
            }

            void pop_back ()
            {
                if (sharing ())
                {
                    make_copy ();
                }

                assert (size () > 0);
                resize (size () - 1);
            }

        public:

            template< typename TYPE >
            TYPE to () const;

        public:

            String substr (size_t start = 0, size_t length = npos) const;

        public:

            size_t find_first_of     (const Char     character,      size_t first_position_to_search = 0   ) const;
            size_t find_first_not_of (const String & character_list, size_t first_position_to_search = 0   ) const;
            size_t find_last_not_of  (const String & character_list, size_t  last_position_to_search = npos) const;

            size_t rfind             (const String & pattern,        size_t  last_position_to_search = npos) const;

            int    compare           (const String & other) const;

        public:

            String & operator =  (const value_type & character)
            {
                return (this->assign (character));
            }

            String & operator =  (const String & other)
            {
                return (this->assign (other));
            }

            String & operator += (const char & character)
            {
                return (this->append (character));
            }

            String & operator += (const wchar_t & character)
            {
                return (this->append (character));
            }

            String & operator += (const value_type & character)
            {
                return (this->append (character));
            }

            String & operator += (const String & other)
            {
                return (this->append (other));
            }

            String & operator += (const char * cstring)
            {
                return (this->append (cstring));
            }

            String & operator += (const wchar_t * wcstring)
            {
                return (this->append (wcstring));
            }

        public:

            String   operator +  (const char & character) const
            {
                return (String(*this) += character);
            }

            String   operator +  (const wchar_t & character) const
            {
                return (String(*this) += character);
            }

            String   operator +  (const value_type & character) const
            {
                return (String(*this) += character);
            }

            String   operator +  (const String & other) const
            {
                return (String(*this) += other);
            }

            String   operator +  (const char * cstring) const
            {
                return (String(*this) += String(cstring));
            }

            String   operator +  (const wchar_t * wcstring) const
            {
                return (String(*this) += String(wcstring));
            }

        public:

            value_type & operator [] (size_t index)
            {
                if (sharing ())
                {
                    make_copy ();
                }

                return (*(characters->begin () + index));
            }

            const value_type & operator [] (size_t index) const
            {
                return (*(characters->begin () + index));
            }

        public:

            bool operator == (const String & other) const;

            bool operator != (const String & other) const
            {
                return not (*this == other);
            }

            bool operator <  (const String & other) const
            {
                return (this->compare (other) <  0);
            }

            bool operator >  (const String & other) const
            {
                return (this->compare (other) >  0);
            }

            bool operator <= (const String & other) const
            {
                return (this->compare (other) <= 0);
            }

            bool operator >= (const String & other) const
            {
                return (this->compare (other) >= 0);
            }

        public:

            operator std::string  () const;
            operator std::wstring () const;
            operator QString      () const;

        private:

            bool sharing ()
            {
                return (not characters.unique ());
            }

            void make_copy ();

        };

        inline void swap (String & a, String & b)
        {
            a.swap (b);
        }

    }

#endif
