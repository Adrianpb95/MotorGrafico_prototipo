
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  ROTATION                                                                   *
 *  Copyright © 2014+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_ROTATION_HEADER
#define TOOLKIT_ROTATION_HEADER

    #include <cmath>
    #include "Transformation.hpp"

    namespace toolkit
    {

        template< size_t DIMENSION, typename NUMERIC_TYPE >
        class Rotation : public Transformation< DIMENSION, NUMERIC_TYPE >
        {
        public:

            Rotation()
            {
            }

        };

        template< typename NUMERIC_TYPE >
        class Rotation< 2, NUMERIC_TYPE > : public Transformation< 2, NUMERIC_TYPE >
        {

            using Transformation< 2, NUMERIC_TYPE >::matrix;

        public:

            typedef NUMERIC_TYPE Numeric_Type;

        public:

            Rotation()
            {
            }

            Rotation(const Numeric_Type & angle)
            {
                set (angle);
            }

        public:

            void set (const Numeric_Type & angle)
            {
                Numeric_Type sin = Numeric_Type(std::sin (angle));
                Numeric_Type cos = Numeric_Type(std::cos (angle));

                matrix[0][0] = cos; matrix[0][1] = -sin;
                matrix[1][0] = sin; matrix[1][1] =  cos;
            }

        };

        template< typename NUMERIC_TYPE >
        class Rotation< 3, NUMERIC_TYPE > : public Transformation< 3, NUMERIC_TYPE >
        {

            using Transformation< 3, NUMERIC_TYPE >::matrix;

        public:

            enum Type
            {
                AROUND_THE_X_AXIS,
                AROUND_THE_Y_AXIS,
                AROUND_THE_Z_AXIS
            };

        public:

            typedef NUMERIC_TYPE Numeric_Type;

        public:

            Rotation()
            {
            }

            /*template< Type TYPE >
            Rotation(const Type & , const Numeric_Type & angle)
            {
                //set< TYPE > (angle);
            }*/

            // AROUND A LINE...

        public:

            template< Type TYPE >
            void set (const Numeric_Type & angle);

        };

        #define SPECIALIZE_ROTATION_3_SET_AROUND_THE_X_AXIS(NUMERIC_TYPE) \
        \
            template< > \
            template< > \
            inline void Rotation< 3, NUMERIC_TYPE >::set< Rotation< 3, NUMERIC_TYPE >::AROUND_THE_X_AXIS > (const NUMERIC_TYPE & angle) \
            { \
                NUMERIC_TYPE sin = NUMERIC_TYPE(std::sin (angle)); \
                NUMERIC_TYPE cos = NUMERIC_TYPE(std::cos (angle)); \
            \
                matrix[1][1] =  cos; matrix[1][2] = -sin; \
                matrix[2][1] =  sin; matrix[2][2] =  cos; \
            }

        #define SPECIALIZE_ROTATION_3_SET_AROUND_THE_Y_AXIS(NUMERIC_TYPE) \
        \
            template< > \
            template< > \
            inline void Rotation< 3, NUMERIC_TYPE >::set< Rotation< 3, NUMERIC_TYPE >::AROUND_THE_Y_AXIS > (const NUMERIC_TYPE & angle) \
            { \
                NUMERIC_TYPE sin = NUMERIC_TYPE(std::sin (angle)); \
                NUMERIC_TYPE cos = NUMERIC_TYPE(std::cos (angle)); \
            \
                matrix[0][0] =  cos; matrix[0][2] =  sin; \
                matrix[2][0] = -sin; matrix[2][2] =  cos; \
            }

        #define SPECIALIZE_ROTATION_3_SET_AROUND_THE_Z_AXIS(NUMERIC_TYPE) \
        \
            template< > \
            template< > \
            inline void Rotation< 3, NUMERIC_TYPE >::set< Rotation< 3, NUMERIC_TYPE >::AROUND_THE_Z_AXIS > (const NUMERIC_TYPE & angle) \
            { \
                NUMERIC_TYPE sin = NUMERIC_TYPE(std::sin (angle)); \
                NUMERIC_TYPE cos = NUMERIC_TYPE(std::cos (angle)); \
            \
                matrix[0][0] =  cos; matrix[0][1] = -sin; \
                matrix[1][0] =  sin; matrix[1][1] =  cos; \
            }

        SPECIALIZE_ROTATION_3_SET_AROUND_THE_X_AXIS(float )
        SPECIALIZE_ROTATION_3_SET_AROUND_THE_X_AXIS(double)
        SPECIALIZE_ROTATION_3_SET_AROUND_THE_Y_AXIS(float )
        SPECIALIZE_ROTATION_3_SET_AROUND_THE_Y_AXIS(double)
        SPECIALIZE_ROTATION_3_SET_AROUND_THE_Z_AXIS(float )
        SPECIALIZE_ROTATION_3_SET_AROUND_THE_Z_AXIS(double)

        typedef Rotation< 2, float  > Rotation2f;
        typedef Rotation< 2, double > Rotation2d;

        typedef Rotation< 3, float  > Rotation3f;
        typedef Rotation< 3, double > Rotation3d;

    }

#endif
