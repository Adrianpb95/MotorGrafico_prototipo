
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  TRANSLATION                                                                *
 *  Copyright © 2014+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_TRANSLATION_HEADER
#define TOOLKIT_TRANSLATION_HEADER

    #include "Vector.hpp"
    #include "Transformation.hpp"

    namespace toolkit
    {

        template< size_t DIMENSION, typename NUMERIC_TYPE >
        class Translation : public Transformation< DIMENSION, NUMERIC_TYPE >
        {
        public:

            Translation()
            {
            }

        };

        template< typename NUMERIC_TYPE >
        class Translation< 2, NUMERIC_TYPE > : public Transformation< 2, NUMERIC_TYPE >
        {

            using Transformation< 2, NUMERIC_TYPE >::matrix;

        public:

            typedef NUMERIC_TYPE Numeric_Type;

        public:

            Translation()
            {
            }

            Translation(const Vector< 2, Numeric_Type > & displacement)
            {
                set (displacement);
            }

            Translation(const Numeric_Type & displacement_x, const Numeric_Type & displacement_y)
            {
                set (displacement_x, displacement_y);
            }

        public:

            void set (const Vector< 2, Numeric_Type > & displacement)
            {
                matrix[0][2] = displacement[0];
                matrix[1][2] = displacement[1];
            }

            void set (const Numeric_Type & displacement_x, const Numeric_Type & displacement_y)
            {
                matrix[0][2] = displacement_x;
                matrix[1][2] = displacement_y;
            }

        };

        template< typename NUMERIC_TYPE >
        class Translation< 3, NUMERIC_TYPE > : public Transformation< 3, NUMERIC_TYPE >
        {

            using Transformation< 3, NUMERIC_TYPE >::matrix;

        public:

            typedef NUMERIC_TYPE Numeric_Type;

        public:

            Translation()
            {
            }

            Translation(const Vector< 3, Numeric_Type > & displacement)
            {
                set (displacement);
            }

            Translation(const Numeric_Type & displacement_x, const Numeric_Type & displacement_y, const Numeric_Type & displacement_z)
            {
                set (displacement_x, displacement_y, displacement_z);
            }

        public:

            void set (const Vector< 3, Numeric_Type > & displacement)
            {
                matrix[0][3] = displacement[0];
                matrix[1][3] = displacement[1];
                matrix[2][3] = displacement[2];
            }

            void set (const Numeric_Type & displacement_x, const Numeric_Type & displacement_y, const Numeric_Type & displacement_z)
            {
                matrix[0][3] = displacement_x;
                matrix[1][3] = displacement_y;
                matrix[2][3] = displacement_z;
            }

        };

        typedef Translation< 2, int    > Translation2i;
        typedef Translation< 2, float  > Translation2f;
        typedef Translation< 2, double > Translation2d;

        typedef Translation< 3, int    > Translation3i;
        typedef Translation< 3, float  > Translation3f;
        typedef Translation< 3, double > Translation3d;

    }

#endif
