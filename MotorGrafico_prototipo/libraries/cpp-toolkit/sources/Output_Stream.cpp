
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  OUTPUT STREAM                                                              *
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
#include <Output_Stream.hpp>

namespace toolkit
{

    template< >
    bool Output_Stream::put< String > (const String & unicode_string)
    {
        /*std::vector< byte > utf8_string;

        convert_string_to_utf8 (unicode_string, utf8_string);

        return
        (
            put< int32_t > (utf8_string.size ()) && write (&utf8_string.front (), utf8_string.size ())
        );*/
        return (false);
    }

    template< >
    bool Output_Stream::put< std::string > (const std::string & ascii_string)
    {
        /*std::vector< byte > utf8_string;

        convert_string_to_utf8 (ascii_string, utf8_string);

        return
        (
            put< int32_t > (utf8_string.size ()) && write (&utf8_string.front (), utf8_string.size ())
        );*/
        return (false);
    }

    template< >
    bool Output_Stream::put< std::wstring > (const std::wstring & unicode_string)
    {
        /*std::vector< byte > utf8_string;

        convert_string_to_utf8 (unicode_string, utf8_string);

        return
        (
            put< int32_t > (utf8_string.size ()) && write (&utf8_string.front (), utf8_string.size ())
        );*/
        return (false);
    }

    template< >
    bool Output_Stream::put< const char * const > (const char * const & ascii_string)
    {
        return (put (std::string(ascii_string)));
    }

    template< >
    bool Output_Stream::put< const wchar_t * const > (const wchar_t * const & unicode_string)
    {
        return (put (std::wstring(unicode_string)));
    }

}
