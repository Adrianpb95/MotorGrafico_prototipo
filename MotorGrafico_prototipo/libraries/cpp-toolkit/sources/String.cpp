
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

#include <String.hpp>

#if defined(TOOLKIT_USING_QT)
    #include <QString>
#endif

namespace toolkit
{

    #if defined(TOOLKIT_USING_QT)

        String::String(const QChar & character)
        :
            characters(new Char_Buffer(1))
        {
            front () = character;
        }

        String::String(const QString & source)
        :
            characters(new Char_Buffer(source.size ()))
        {
            if (not source.isEmpty ())
            {
                std::copy (source.begin (), source.end (), begin ());
            }
        }

    #endif

    String & String::append (const Char & character)
    {
        if (sharing ())
        {
            make_copy ();
        }

        characters->enlarge (1);

        back () = character;

        return (*this);
    }

    String & String::append (const String & other)
    {
        if (other.size () > 0)
        {
            if (sharing ())
            {
                make_copy ();
            }

            size_t initial_size = size ();

            characters->enlarge (other.size ());

            std::copy (other.begin (), other.end (), begin () + initial_size);
        }

        return (*this);
    }

    String & String::append (const char * cstring)
    {
        if (cstring)
        {
            size_t cstring_size = std::strlen (cstring);

            if (cstring_size > 0)
            {
                if (sharing ())
                {
                    make_copy ();
                }

                size_t initial_size = size ();

                characters->enlarge (cstring_size);

                std::copy (cstring, cstring + cstring_size, begin () + initial_size);
            }
        }

        return (*this);
    }

    String & String::append (const wchar_t * wcstring)
    {
        if (wcstring)
        {
            size_t wcstring_size = std::wcslen (wcstring);

            if (wcstring_size > 0)
            {
                if (sharing ())
                {
                    make_copy ();
                }

                size_t initial_size = size ();

                characters->enlarge (wcstring_size);

                std::copy (wcstring, wcstring + wcstring_size, begin () + initial_size);
            }
        }

        return (*this);
    }

    void String::swap (String & other)
    {
        if (this->characters != other.characters)
        {
            Shared_Ptr< Char_Buffer > characters_holder = this->characters;

            this->characters = other.characters;
            other.characters = characters_holder;
        }
    }

    template< >
    std::string String::to< std::string > () const
    {
        std::string replica(begin (), end ());

        return (replica);
    }

    template< >
    std::wstring String::to< std::wstring > () const
    {
        std::wstring replica(begin (), end ());

        return (replica);
    }

    #if defined(TOOLKIT_USING_QT)

        template< >
        QString String::to< QString > () const
        {
            QString replica;

            replica.resize (size ());

            std::copy (begin (), end (), replica.begin ());

            return (replica);
        }

    #endif

    String String::substr (size_t start, size_t length) const
    {
        if (start < size () && length > 0)
        {
            if (length > size () - start)           // Cuando length=npos, la suma produce un rollover... ':|
            {
                length = size () - start;
            }

            const_iterator substr_begin = this-> begin () + start;
            const_iterator substr_end   = substr_begin    + length;

            if (substr_end > this->end ())
            {
                substr_end = this->end ();
            }

            String substr(substr_end - substr_begin);

            std::copy (substr_begin, substr_end, substr.begin ());

            return (substr);
        }

        return (String());
    }

    size_t String::find_first_of (const Char character, size_t first_position_to_search) const
    {
        if (first_position_to_search < size ())
        {
            for (const_iterator i = begin () + first_position_to_search; i != end (); i++)
            {
                if (*i == character)
                {
                    return (i - begin ());
                }
            }
        }

        return (npos);
    }

    size_t String::find_first_not_of (const String & character_list, size_t first_position_to_search) const
    {
        if (first_position_to_search < size () && character_list.size () > 0)
        {
            const_iterator character_list_begin = character_list.begin ();
            const_iterator character_list_end   = character_list.end   ();

            for (const_iterator this_iterator = this->begin () + first_position_to_search; this_iterator != this->end (); this_iterator++)
            {
                value_type     current_character       = *this_iterator;
                const_iterator character_list_iterator =  character_list_begin;

                while (character_list_iterator != character_list_end)
                {
                    if (current_character == *character_list_iterator)
                    {
                        break;
                    }

                    character_list_iterator++;
                }

                if (character_list_iterator == character_list_end)
                {
                    return (this_iterator - this->begin ());
                }
            }
        }

        return (npos);
    }

    size_t String::find_last_not_of (const String & character_list, size_t last_position_to_search) const
    {
        if (this->size () > 0 && character_list.size () > 0)
        {
            const_iterator character_list_begin = character_list.begin ();
            const_iterator character_list_end   = character_list.end   ();
            const_iterator this_begin           = this->begin ();
            const_iterator this_end             = this->end   ();
            const_iterator this_iterator;

            if (last_position_to_search == npos)
            {
                this_iterator = this_end - 1;
            }
            else
            {
                this_iterator = this_begin + last_position_to_search;

                if (this_iterator >= this_end)
                {
                    this_iterator  = this_end - 1;
                }
            }

            while (this_iterator >= this_begin)
            {
                value_type     current_character       = *this_iterator;
                const_iterator character_list_iterator =  character_list_begin;

                while (character_list_iterator != character_list_end)
                {
                    if (current_character == *character_list_iterator)
                    {
                        break;
                    }

                    character_list_iterator++;
                }

                if (character_list_iterator == character_list_end)
                {
                    return (this_iterator - this_begin);
                }

                this_iterator--;
            }
        }

        return (npos);
    }

    size_t String::rfind (const String & pattern, size_t last_position_to_search) const
    {
        if (this->size () > 0 && pattern.size () > 0 && pattern.size () <= this->size ())
        {
            const_iterator pattern_begin = pattern.begin ();
            const_iterator pattern_end   = pattern.end   ();
            value_type     pattern_front = pattern.front ();

            const_iterator this_begin    = this->  begin ();
            const_iterator this_end      = this->  end   ();
            const_iterator this_iterator;

            if (last_position_to_search == npos)
            {
                this_iterator = this_end - pattern.size ();
            }
            else
            {
                this_iterator = this_begin + last_position_to_search;

                if (this_iterator > this_end - pattern.size ())
                {
                    this_iterator = this_end - pattern.size ();
                }
            }

            while (this_iterator >= this_begin)
            {
                if (*this_iterator == pattern_front)
                {
                    const_iterator a = this_iterator + 1;
                    const_iterator b = pattern_begin + 1;

                    while (a != this_end && b != pattern_end)
                    {
                        if (*a++ != *b++)
                        {
                            break;
                        }
                    }

                    if (b == pattern_end)
                    {
                        return size_t(this_iterator - this_begin);
                    }
                }

                this_iterator--;
            }
        }

        return (npos);
    }

    int String::compare (const String & other) const
    {
        if (this->characters != other.characters)
        {
            int common_size = std::min (this->size (), other.size ());

            for (const_iterator a = this->begin (), b = other.begin (), end = a + common_size; a != end; a++, b++)
            {
                if (*a < *b) { return (-1); } else if (*a > *b) { return (+1); }
            }

            return (this->size () - other.size ());
        }

        return (0);
    }

    bool String::operator == (const String & other) const
    {
        if (this->characters != other.characters)
        {
            if (this->characters->size () == other.characters->size ())
            {
                for (const_iterator a = this->begin (), b = other.begin (); a != this->end (); a++, b++)
                {
                    if (*a != *b)
                    {
                        return (false);
                    }
                }

                return (true);
            }

            return (false);
        }

        return (true);
    }

    String::operator std::string () const
    {
        return (this->to< std::string > ());
    }

    String::operator std::wstring () const
    {
        return (this->to< std::wstring > ());
    }

    #if defined(TOOLKIT_USING_QT)

        String::operator QString () const
        {
            return (this->to< QString > ());
        }

    #endif

    void String::make_copy ()
    {
        Shared_Ptr< Char_Buffer > own_buffer(new Char_Buffer(characters->size ()));

        std::copy (characters->begin (), characters->end (), own_buffer->begin ());

        characters = own_buffer;
    }

}
