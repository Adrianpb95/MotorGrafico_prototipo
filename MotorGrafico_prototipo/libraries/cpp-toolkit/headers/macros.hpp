
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  MACROS                                                                     *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_MACROS_HEADER
#define TOOLKIT_MACROS_HEADER

    #if defined(__GNUC__)

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
         *                             GNU COMPILER                            *
        \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        #define TOOLKIT_GNU_COMPILER
        #define TOOLKIT_COMPILER_VERSION  __GNUC__
        #define TOOLKIT_COMPILER_REVISION __GNUC_MINOR__

        #define TOOLKIT_LITTLE_ENDIAN       // BEWARE!!!

        #ifdef __EXCEPTIONS
            #define TOOLKIT_EXCEPTIONS_ENABLED
        #endif

        #ifdef __GXX_RTTI
            #define TOOLKIT_RTTI_ENABLED
        #endif

        #if defined(__MINGW32__) || defined(__MINGW64__)
            #define TOOLKIT_WINDOWS_API
            #if defined(__x86_64)
                #define TOOLKIT_WORD_SIZE 64
            #else
                #define TOOLKIT_WORD_SIZE 32
            #endif
            #ifndef __MSVCRT_VERSION__                  // This restricts compatibility but provides functionality
                #define __MSVCRT_VERSION__ 0x0800       // Requires linking with libmsvcr80.a (-lmsvcr80) or above
                #ifndef FILENAME_MAX
                    #define FILENAME_MAX 260            // This prevents an old bug in wchar.h (it may be removed)
                #endif
            #endif
        #elif defined(__CYGWIN__)
            #define TOOLKIT_POSIX_API
            #define TOOLKIT_WINDOWS_API
            #if defined(__x86_64)
                #define TOOLKIT_WORD_SIZE 64
            #else
                #define TOOLKIT_WORD_SIZE 32
            #endif
        #elif defined(_WIN64)
            #define TOOLKIT_WINDOWS_API
            #define TOOLKIT_WORD_SIZE 64
        #elif defined (_WIN32)
            #define TOOLKIT_WINDOWS_API
            #define TOOLKIT_WORD_SIZE 32
        #elif defined(__APPLE__)
            #define TOOLKIT_MAC_OS_API
        #endif

        #ifndef NDEBUG
            #ifdef __OPTIMIZE__
                #ifndef NDEBUG
                    #define NDEBUG
                #endif
            #else
                #define TOOLKIT_DEBUG
            #endif
        #endif

        #define TOOLKIT_STDINT_HEADER "stdint.h"

    #elif defined(_MSC_VER)

        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
         *                         MICROSOFT VISUAL C++                        *
        \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        #define TOOLKIT_MICROSOFT_COMPILER
        #define TOOLKIT_COMPILER_VERSION   (_MSC_VER / 100)
        #define TOOLKIT_COMPILER_REVISION  (_MSC_VER % 100)

        #define TOOLKIT_LITTLE_ENDIAN       // BEWARE WITH WINDOWS RT!!!

        #ifdef _CPPUNWIND
            #define TOOLKIT_EXCEPTIONS_ENABLED
        #endif

        #ifdef _CPPRTTI
            #define TOOLKIT_RTTI_ENABLED
        #endif

        #ifndef NDEBUG
            #ifdef _DEBUG
                #define TOOLKIT_DEBUG
            #else
                #ifndef NDEBUG
                    #define NDEBUG
                #endif
            #endif
        #endif

        #if (_MSC_VER >= 1600)
            #define TOOLKIT_CPP11_KEYWORDS_AVAILABLE
            #define TOOLKIT_CPP11_LIBRARIES_AVAILABLE
        #endif

        #define TOOLKIT_STDINT_HEADER "stdint.h"

        // El compilador de Microsoft no define estos operadores y Marmalade SDK no da
        // acceso a la cabecera <ciso646>:

        #define and     &&
        #define and_eq  &=
        #define bitand  &
        #define bitor   |
        #define compl   ~
        #define not     !
        #define not_eq  !=
        #define or      ||
        #define or_eq   |=
        #define xor     ^
        #define xor_eq  ^=

    #endif

    #if !defined(TOOLKIT_DEBUG) && defined(QT_DEBUG)
        #define  TOOLKIT_DEBUG
    #endif

    #if !defined(TOOLKIT_DEBUG)
        #define  TOOLKIT_RELEASE
    #endif

    #if defined(QT_DEBUG) || defined(QT_NO_DEBUG) || defined(QT_DLL) || defined(QT_CORE_LIB)
        #define TOOLKIT_USING_QT
    #endif

    #include <cstddef>

#endif
