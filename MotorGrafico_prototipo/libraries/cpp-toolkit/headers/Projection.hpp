
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  PROJECTION                                                                 *
 *  Copyright © 2014+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_PROJECTION_HEADER
#define TOOLKIT_PROJECTION_HEADER

    #include <cmath>
    #include "Transformation.hpp"

    namespace toolkit
    {

        template< size_t DIMENSION, typename NUMERIC_TYPE >
        class Projection : public Transformation< DIMENSION, NUMERIC_TYPE >
        {
        public:

            Projection()
            {
            }

        };

        template< typename NUMERIC_TYPE >
        class Projection< 3, NUMERIC_TYPE > : public Transformation< 3, NUMERIC_TYPE >
        {
        public:

            typedef NUMERIC_TYPE Numeric_Type;

        public:

            Projection(const Numeric_Type & near_z, const Numeric_Type & far_z, const Numeric_Type & fov_in_degrees, const Numeric_Type & aspect_ratio)
            {
                set (near_z, far_z, fov_in_degrees, aspect_ratio);
            }

        public:

            void set  (const Numeric_Type & near_z, const Numeric_Type & far_z, const Numeric_Type & fov_in_degrees, const Numeric_Type & aspect_ratio)
            {
                Numeric_Type depth_divisor = Numeric_Type(1)  / (far_z - near_z);
                Numeric_Type scale         = Numeric_Type(1.0 /  std::tan (fov_in_degrees * 0.5 * 3.141592653589793238 / 180.0));

                matrix[0][0] =  scale / aspect_ratio;
                matrix[1][1] =  scale;
                matrix[2][2] = -(near_z + far_z) * depth_divisor;
                matrix[2][3] =  Numeric_Type(-2) * depth_divisor * near_z * far_z;
                matrix[3][2] =  Numeric_Type(-1);
                matrix[3][3] =  Numeric_Type( 0);
            }

        };

        typedef Projection< 3, int    > Projection3i;
        typedef Projection< 3, float  > Projection3f;
        typedef Projection< 3, double > Projection3d;

    }

#endif
