
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  SCALING                                                                    *
 *  Copyright © 2014+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_SCALING_HEADER
#define TOOLKIT_SCALING_HEADER

    #include "Transformation.hpp"

    namespace toolkit
    {

        template< size_t DIMENSION, typename NUMERIC_TYPE >
        class Scaling : public Transformation< DIMENSION, NUMERIC_TYPE >
        {
        public:

            Scaling()
            {
            }

        };

        template< typename NUMERIC_TYPE >
        class Scaling< 2, NUMERIC_TYPE > : public Transformation< 2, NUMERIC_TYPE >
        {

            using Transformation< 2, NUMERIC_TYPE >::matrix;

        public:

            typedef NUMERIC_TYPE Numeric_Type;

        public:

            Scaling()
            {
            }

            Scaling(const Numeric_Type & value)
            {
                set (value);
            }

            Scaling(const Numeric_Type & value_x, const Numeric_Type & value_y)
            {
                set (value_x, value_y);
            }

        public:

            void set (const Numeric_Type & value)
            {
                set (value, value);
            }

            void set (const Numeric_Type & value_x, const Numeric_Type & value_y)
            {
                matrix[0][0] = value_x;
                matrix[1][1] = value_y;
            }

        };

        template< typename NUMERIC_TYPE >
        class Scaling< 3, NUMERIC_TYPE > : public Transformation< 3, NUMERIC_TYPE >
        {

            using Transformation< 3, NUMERIC_TYPE >::matrix;

        public:

            typedef NUMERIC_TYPE Numeric_Type;

        public:

            Scaling()
            {
            }

            Scaling(const Numeric_Type & value)
            {
                set (value);
            }

            Scaling(const Numeric_Type & value_x, const Numeric_Type & value_y, const Numeric_Type & value_z)
            {
                set (value_x, value_y, value_z);
            }

        public:

            void set (const Numeric_Type & value)
            {
                set (value, value, value);
            }

            void set (const Numeric_Type & value_x, const Numeric_Type & value_y, const Numeric_Type & value_z)
            {
                matrix[0][0] = value_x;
                matrix[1][1] = value_y;
                matrix[2][2] = value_z;
            }

        };

        typedef Scaling< 2, int    > Scaling2i;
        typedef Scaling< 2, float  > Scaling2f;
        typedef Scaling< 2, double > Scaling2d;

        typedef Scaling< 3, int    > Scaling3i;
        typedef Scaling< 3, float  > Scaling3f;
        typedef Scaling< 3, double > Scaling3d;

    }

#endif
