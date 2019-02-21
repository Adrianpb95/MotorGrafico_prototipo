
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

#ifndef TOOLKIT_INPUT_STREAM_HEADER
#define TOOLKIT_INPUT_STREAM_HEADER

    #include "Stream.hpp"

    namespace toolkit
    {

        class Input_Stream : public Stream< Input_Stream >
        {
        public:

            virtual ~Input_Stream()
            {
            }

        public:

            // Quizás la principal ventaja de usar templates para get() es que se pueden añadir
            // especializaciones para cualquier nuevo tipo sin necesidad de modificar Input_Stream.

            template< typename TYPE >
            TYPE get ()
            {
                TYPE    buffer;
                get    (buffer);
                return (buffer);
            }

            // Por defecto no hay implementación para un tipo cualquiera. Hay que hacer una
            // especializaciones apropiadas para cada tipo.

            template< typename TYPE >
            bool get (TYPE & instance);

            template< class CONTAINER_TYPE >
            bool read_all  (CONTAINER_TYPE & container);

        public:

            virtual byte     get  () = 0;
            virtual uint64_t read (byte * buffer, size_t size) = 0;

        };

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        template< >
        inline int8_t  Input_Stream::get<  int8_t > ()
        {
            return  int8_t(get ());
        }

        template< >
        inline uint8_t Input_Stream::get< uint8_t > ()
        {
            return uint8_t(get ());
        }

        #if defined(TOOLKIT_LITTLE_ENDIAN)

            #define IMPLEMENT_PLAIN_GET_FOR(TYPE) \
                template< > \
                inline bool Input_Stream::get< TYPE > (TYPE & instance) \
                { \
                    return (read (reinterpret_cast< byte * >(&instance), sizeof(TYPE)) == sizeof(TYPE) && good ()); \
                }

            IMPLEMENT_PLAIN_GET_FOR(  int8_t)
            IMPLEMENT_PLAIN_GET_FOR( int16_t)
            IMPLEMENT_PLAIN_GET_FOR( int32_t)
            IMPLEMENT_PLAIN_GET_FOR( int64_t)

            IMPLEMENT_PLAIN_GET_FOR( uint8_t)
            IMPLEMENT_PLAIN_GET_FOR(uint16_t)
            IMPLEMENT_PLAIN_GET_FOR(uint32_t)
            IMPLEMENT_PLAIN_GET_FOR(uint64_t)

            IMPLEMENT_PLAIN_GET_FOR(   float)           // Se presupone siempre de 32 bits
            IMPLEMENT_PLAIN_GET_FOR(  double)           // Se presupone siempre de 64 bits

            template< >
            inline bool Input_Stream::get< bool > (bool & instance)
            {
                instance = get () != 0;
                return (good ());
            }

            template< >
            inline bool Input_Stream::get< char > (char & instance)
            {
                instance = char(get< uint8_t > ());
                return (good ());
            }

            template< >
            inline bool Input_Stream::get< wchar_t > (wchar_t & instance)
            {
                instance = wchar_t(get< uint16_t > ());
                return (good ());
            }

        #else

            #error "There're not specializations of Input_Stream::get<T>(T&) for big endian architectures yet."

        #endif

    }

#endif
