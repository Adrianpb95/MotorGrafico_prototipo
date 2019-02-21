
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  INPUT STREAM                                                               *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <vector>
#include <String.hpp>
#include <Input_Stream.hpp>

#if defined(TOOLKIT_USING_QT)
    #include <QByteArray>
#endif

namespace toolkit
{

    template< >
    bool Input_Stream::get< String > (String & unicode_string)
    {
        /*int utf8_string_length = get< int32_t > ();

        if (good ())
        {
            if (utf8_string_length == 0)
            {
                unicode_string.clear ();

                return (true);
            }
            else
            {
                assert(utf8_string_length < 1024*1024);                 // Por precaución...

                std::vector< byte > utf8_string(utf8_string_length);

                if (read (&utf8_string.front (), utf8_string.size ()))
                {
                    convert_utf8_to_string (utf8_string, unicode_string);

                    return (true);
                }
            }
        }*/

        return (false);
    }

    template< >
    bool Input_Stream::get< std::wstring > (std::wstring & unicode_string)
    {
        /*int utf8_string_length = get< int32_t > ();

        if (good ())
        {
            if (utf8_string_length == 0)
            {
                unicode_string.clear ();

                return (true);
            }
            else
            {
                assert(utf8_string_length < 1024*1024);                 // Por precaución...

                std::vector< byte > utf8_string(utf8_string_length);

                if (read (&utf8_string.front (), utf8_string.size ()))
                {
                    convert_utf8_to_string (utf8_string, unicode_string);

                    return (true);
                }
            }
        }*/

        return (false);
    }

    template< >
    bool Input_Stream::read_all (std::vector< byte > & container)
    {
        byte read_buffer[4096u];

        while (good ())
        {
            size_t read_size = size_t(read (read_buffer, 4096u));

            container.insert (container.end (), read_buffer, read_buffer + read_size);
        }

        return (eos () == true /*&& not bad ()*/);
    }

    #if defined(TOOLKIT_USING_QT)

        template< >
        bool Input_Stream::read_all (QByteArray & container)
        {
            byte read_buffer[4096u];

            while (good ())
            {
                size_t read_size = read (read_buffer, 4096u);

                container.append (reinterpret_cast< const char * >(read_buffer), read_size);
            }

            return (eos () == true /*&& not bad ()*/);
        }

    #endif

}
