
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

#ifndef TOOLKIT_OUTPUT_STREAM_HEADER
#define TOOLKIT_OUTPUT_STREAM_HEADER

    #include "Stream.hpp"

    namespace toolkit
    {

        class Output_Stream : public Stream< Output_Stream >
        {
        public:

            virtual ~Output_Stream()
            {
            }

        public:

            // Quizás la principal ventaja de usar templates para put() es que se pueden añadir
            // especializaciones para cualquier nuevo tipo sin necesidad de modificar Output_Stream.
            // Por defecto no hay implementación para un tipo cualquiera. Hay que hacer una
            // especializaciones apropiadas para cada tipo.

            template< typename TYPE >
            bool put (const TYPE & instance);

        public:

            virtual bool put   (byte value) = 0;
            virtual bool write (const byte * buffer, size_t size) = 0;

        };

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        #if defined(TOOLKIT_LITTLE_ENDIAN)

            #define IMPLEMENT_PLAIN_PUT_FOR(TYPE) \
                template< > \
                inline bool Output_Stream::put< TYPE > (const TYPE & instance) \
                { \
                    return (write (reinterpret_cast< const byte * >(&instance), sizeof(TYPE))); \
                }

            IMPLEMENT_PLAIN_PUT_FOR(  int8_t)
            IMPLEMENT_PLAIN_PUT_FOR( int16_t)
            IMPLEMENT_PLAIN_PUT_FOR( int32_t)
            IMPLEMENT_PLAIN_PUT_FOR( int64_t)

            IMPLEMENT_PLAIN_PUT_FOR( uint8_t)
            IMPLEMENT_PLAIN_PUT_FOR(uint16_t)
            IMPLEMENT_PLAIN_PUT_FOR(uint32_t)
            IMPLEMENT_PLAIN_PUT_FOR(uint64_t)

            IMPLEMENT_PLAIN_PUT_FOR(   float)           // Se presupone siempre de 32 bits
            IMPLEMENT_PLAIN_PUT_FOR(  double)           // Se presupone siempre de 64 bits

            template< >
            inline bool Output_Stream::put< bool    > (const bool    & value)
            {
                return (put (value ? 1 : 0));
            }

            template< >
            inline bool Output_Stream::put< char    > (const char    & value)
            {
                return (put< uint8_t  > (value));
            }

            template< >
            inline bool Output_Stream::put< wchar_t > (const wchar_t & value)
            {
                return (put< uint16_t > (value));
            }

        #else

            #error "There're not specializations of Output_Stream::put<T>(const T&) for big endian architectures yet."

        #endif

    }

#endif
