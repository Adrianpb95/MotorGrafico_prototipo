
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  FILE READER                                                                *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_FILE_READER_HEADER
#define TOOLKIT_FILE_READER_HEADER

    #include <fstream>
    #include "Reader.hpp"

    namespace toolkit
    {

        class File_Reader : public Reader, public Seekable, public Cloneable< Input_Stream >
        {
        private:

            std::string     path;
            std::ifstream   owned_ifstream;
            std::ifstream & file_stream;

        public:

            File_Reader(std::ifstream & given_ifstream)
            :
                file_stream(given_ifstream)
            {
            }

            File_Reader(const std::string & file_path, std::ifstream::pos_type start_offset = 0)
            :
                path          (file_path),
                owned_ifstream(file_path.c_str (), std::ifstream::in | std::ifstream::binary),
                file_stream   (owned_ifstream)
            {
                if (start_offset > 0)
                {
                    file_stream.seekg (start_offset);
                }
            }

        public:

            bool seek (uint64_t location)
            {
                file_stream.seekg (std::ifstream::pos_type(location));

                return (not file_stream.fail ());
            }

            uint64_t tell ()
            {
                return (file_stream.tellg ());
            }

            void close ()
            {
                file_stream.close ();
            }

        public:

            uint64_t read (byte * buffer, size_t size)
            {
                file_stream.read (reinterpret_cast< char * >(buffer), size);

                return (file_stream.gcount ());
            }

            byte get  ()       { return (file_stream.get  ()); }
            bool good () const { return (file_stream.good ()); }
            bool fail () const { return (file_stream.fail ()); }
            bool eos  () const { return (file_stream.eof  ()); }

        public:

            Shared_Ptr< Input_Stream > clone () const
            {
                Shared_Ptr< Input_Stream > result;

                if (not path.empty ())
                {
                    result.reset (new File_Reader(path, 0));
                }

                return (result);
            }

        public:

            using Input_Stream::get;

        };

    }

#endif
