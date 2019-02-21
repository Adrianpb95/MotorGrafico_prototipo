
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  FILE WRITER                                                                *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Añadir algún parámetro al primer constructor para permitir indicar si se desea
// truncar o añadir o si se desea crear o fallar si el archivo no existe.

#ifndef TOOLKIT_FILE_WRITER_HEADER
#define TOOLKIT_FILE_WRITER_HEADER

    #include <fstream>
    #include "Writer.hpp"
    #include "Seekable.hpp"
    #include "Cloneable.hpp"

    namespace toolkit
    {

        class File_Writer : public Writer, public Seekable, public Cloneable< Output_Stream >
        {
        private:

            std::string     path;
            std::ofstream   owned_ofstream;
            std::ofstream & file_stream;

        public:

            File_Writer(std::ofstream & given_ofstream)
            :
                file_stream(given_ofstream)
            {
            }

            File_Writer(const std::string & file_path)
            :
                path          (file_path),
                owned_ofstream(file_path.c_str (), std::ofstream::out | std::ofstream::binary | std::ofstream::trunc),
                file_stream   (owned_ofstream)
            {
            }

            File_Writer(const std::string & file_path, std::ofstream::pos_type start_offset)
            :
                path          (file_path),
                owned_ofstream(file_path.c_str (), std::ofstream::out | std::ofstream::binary | std::ofstream::app),
                file_stream   (owned_ofstream)
            {
                file_stream.seekp (start_offset);
            }

        public:

            bool seek (uint64_t location)
            {
                file_stream.seekp (std::ofstream::pos_type(location));

                return (file_stream.fail () == false);
            }

            uint64_t tell ()
            {
                return (size_t(file_stream.tellp ()));
            }

            bool flush ()
            {
                file_stream.flush ();

                return (good ());
            }

            void close ()
            {
                file_stream.close ();
            }

        public:

            bool write (const byte * buffer, size_t size)
            {
                file_stream.write (reinterpret_cast< const char * >(buffer), size);

                return (file_stream.good ());
            }

            bool put (byte value)
            {
                file_stream.put (value);

                return (file_stream.good ());
            }

            bool good () const { return (file_stream.good ()); }
            bool fail () const { return (file_stream.fail ()); }
            bool eos  () const { return (file_stream.eof  ()); }

        public:

            Shared_Ptr< Output_Stream > clone () const
            {
                Shared_Ptr< Output_Stream > result;

                if (not path.empty ())
                {
                    result.reset (new File_Writer(path, 0));
                }

                return (result);
            }

        public:

            using Output_Stream::put;

        };

    }

#endif
