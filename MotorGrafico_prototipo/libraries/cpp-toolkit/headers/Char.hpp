
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  CHAR                                                                       *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_CHAR_HEADER
#define TOOLKIT_CHAR_HEADER

    #include "types.hpp"

    namespace toolkit
    {

        class Char
        {
        public:

            typedef int_fast32_t value_type;

        private:

            value_type value;

        public:

            Char()
            {
            }

            Char(const Char & other)
            {
                this->value = other.value;
            }

            // Implicit conversion constructors:

            Char(const char         & character) { value = value_type(uint8_t (character)); }
            Char(const wchar_t      & character) { value = value_type(uint16_t(character)); }
            Char(const signed int   & code     ) { value = value_type(         code      ); }
            Char(const unsigned int & code     ) { value = value_type(         code      ); }

        public:

            bool is_binary_digit () const
            {
                return  (value == 48 || value == 49);
            }

            bool is_decimal_digit () const
            {
                return  (value >= 48 && value <= 57);
            }

            bool is_hexadecimal_digit () const
            {
                return ((value >= 48 && value <= 57) || (value >= 65 && value <= 70 ));
            }

            bool is_english_letter () const
            {
                return ((value >= 65 && value <= 90) || (value >= 97 && value <= 122));
            }

            bool is_control_character () const
            {
                return  (value <= 31 || (value >= 127 && value <= 159));
            }

            bool is_within_7bit () const
            {
                return  (value <= 127);
            }

            bool is_within_8bit () const
            {
                return  (value <= 255);
            }

        public:

            // Implicit conversion operators overload:

            operator         char () const { return ((        char)value); }
            operator      wchar_t () const { return ((     wchar_t)value); }
            operator   signed int () const { return ((  signed int)value); }
            operator unsigned int () const { return ((unsigned int)value); }

        public:

            // Comparison operators overload:

            bool operator == (const Char & other) const { return (this->value == other.value); }
            bool operator != (const Char & other) const { return (this->value != other.value); }
            bool operator <  (const Char & other) const { return (this->value <  other.value); }
            bool operator >  (const Char & other) const { return (this->value >  other.value); }
            bool operator <= (const Char & other) const { return (this->value <= other.value); }
            bool operator >= (const Char & other) const { return (this->value >= other.value); }

        };

    }

#endif
