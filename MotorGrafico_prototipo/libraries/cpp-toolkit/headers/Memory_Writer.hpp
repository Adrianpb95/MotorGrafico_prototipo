
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  MEMORY WRITER                                                              *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_MEMORY_WRITER_HEADER
#define TOOLKIT_MEMORY_WRITER_HEADER

    #include "Writer.hpp"
    #include "Seekable.hpp"
    #include "Cloneable.hpp"

    namespace toolkit
    {

        class Memory_Writer : public Writer, public Seekable, public Cloneable< Output_Stream >
        {
        private:

            enum
            {
                GOOD, EOS, ERROR
            };

            byte * const begin;
            byte *       iterator;
            byte * const end;
            int          flags;

        public:

            Memory_Writer(byte * given_begin, size_t size)
            :
                begin   (given_begin),
                iterator(given_begin),
                end     (given_begin + size),
                flags   (begin == null ? ERROR : iterator < end ? 0 : EOS)
            {
            }

            Memory_Writer(byte * given_begin, byte * given_end)
            :
                begin   (given_begin),
                iterator(given_begin),
                end     (given_end  ),
                flags   (begin == null || begin > end ? ERROR : iterator < end ? 0 : EOS)
            {
            }

            Memory_Writer(const Memory_Writer & other)
            :
                begin   (other.begin),
                iterator(other.begin),
                end     (other.end  ),
                flags   (other.flags)
            {
            }

        public:

            bool seek (uint64_t location)
            {
                if (not fail () && location <= size_t(end - begin))
                {
                    iterator = begin + location;

                    return (true);
                }

                return (false);
            }

            uint64_t tell ()
            {
                if (not fail ())
                {
                    return size_t(iterator - begin);
                }

                return (0);
            }

        public:

            bool write (const byte * buffer, size_t size)
            {
                if (good ())
                {
                    size_t writeable_size = end - iterator;

                    if (writeable_size >= size)
                    {
                        for (const byte * const write_end = iterator + size; iterator < write_end; )
                        {
                            *iterator++ = *buffer++;
                        }

                        return (true);
                    }

                    flags |= EOS;
                }

                return (false);
            }

            bool put (byte value)
            {
                if (good ())
                {
                    if (iterator < end)
                    {
                        *iterator++ = value;

                        return (true);
                    }

                    flags |= EOS;
                }

                return (false);
            }

        public:

            bool good () const { return ((flags == GOOD )     ); }
            bool fail () const { return ((flags &  ERROR) != 0); }
            bool eos  () const { return ((flags &  EOS  ) != 0); }

        public:

            Shared_Ptr< Output_Stream > clone () const
            {
                return (Shared_Ptr< Output_Stream >(new Memory_Writer(*this)));
            }

        public:

            using Output_Stream::put;

        };

    }

#endif
