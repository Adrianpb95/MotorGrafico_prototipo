
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  MEMORY READER                                                              *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_MEMORY_READER_HEADER
#define TOOLKIT_MEMORY_READER_HEADER

    #include "Reader.hpp"
    #include "Seekable.hpp"
    #include "Cloneable.hpp"

    namespace toolkit
    {

        class Memory_Reader : public Reader, public Seekable, public Cloneable< Input_Stream >
        {
        private:

            enum
            {
                GOOD, EOS, ERROR
            };

            const byte * const begin;
            const byte *       iterator;
            const byte * const end;
            int                flags;

        public:

            Memory_Reader(const byte * given_begin, size_t size)
            :
                begin   (given_begin),
                iterator(given_begin),
                end     (given_begin + size)
            {
                flags = begin == null ? ERROR : iterator < end ? 0 : EOS;
            }

            Memory_Reader(const byte * given_begin, const byte * given_end)
            :
                begin   (given_begin),
                iterator(given_begin),
                end     (given_end  )
            {
                flags = begin == null ? ERROR : iterator < end ? 0 : EOS;
            }

            Memory_Reader(const Memory_Reader & other)
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

            uint64_t read (byte * buffer, size_t size)
            {
                if (good ())
                {
                    size_t readable_size = end - iterator;

                    if (readable_size < size)
                    {
                        size   = readable_size;
                        flags |= EOS;
                    }

                    for (const byte * const read_end = iterator + size; iterator < read_end; )
                    {
                        *buffer++ = *iterator++;
                    }

                    return (size);
                }

                return (0);
            }

            byte get ()
            {
                if (good ())
                {
                    if (iterator < end)
                    {
                        return (*iterator++);
                    }

                    flags |= EOS;
                }

                return (0);
            }

        public:

            bool good () const { return ((flags == GOOD )     ); }
            bool fail () const { return ((flags &  ERROR) != 0); }
            bool eos  () const { return ((flags &  EOS  ) != 0); }

        public:

            Shared_Ptr< Input_Stream > clone () const
            {
                return (Shared_Ptr< Input_Stream >(new Memory_Reader(*this)));
            }

        public:

            using Input_Stream::get;

        };

    }

#endif
