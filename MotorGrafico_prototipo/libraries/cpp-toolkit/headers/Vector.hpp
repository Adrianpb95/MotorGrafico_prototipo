
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  VECTOR                                                                     *
 *  Copyright © 2012+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_VECTOR_HEADER
#define TOOLKIT_VECTOR_HEADER

    #include "Coordinates.hpp"

    namespace toolkit
    {

        template< size_t DIMENSION, typename NUMERIC_TYPE, bool SPECIALIZATION = true >
        class Vector : public Coordinates< DIMENSION, NUMERIC_TYPE >
        {
        public:

            typedef Coordinates< DIMENSION, NUMERIC_TYPE > Coordinates_Type;
            typedef Coordinates_Type                       Parent;
            typedef NUMERIC_TYPE                           Numeric_Type;
            static  const size_t                           dimension = DIMENSION;

        public:

            Vector()
            {
            }

            Vector(const Vector & other) : Parent(other)
            {
            }

            Vector(const Numeric_Type (& given_values)[dimension]) : Parent(given_values)
            {
            }

            Vector(const Coordinates_Type & given_Coordinates) : Parent(given_Coordinates)
            {
            }

            Vector(const Matrix< 1, DIMENSION, Numeric_Type > & matrix) : Parent(reinterpret_cast< const Vector & >(matrix))
            {
            }

            Vector(const Matrix< DIMENSION, 1, Numeric_Type > & matrix) : Parent(reinterpret_cast< const Vector & >(matrix))
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Vector(const OTHER_NUMERIC_TYPE (& given_values)[dimension]) : Parent(given_values)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Vector(const Vector< dimension, OTHER_NUMERIC_TYPE > & other) : Parent(other)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Vector(const Coordinates< dimension, OTHER_NUMERIC_TYPE > & given_Coordinates) : Parent(given_Coordinates)
            {
            }

        private:

            // Make private these inherited methods:

                  Numeric_Type (& get_values ()      )[dimension];
            const Numeric_Type (& get_values () const)[dimension];

        public:

            Coordinates_Type & coordinates ()
            {
                return (static_cast< Coordinates_Type & >(*this));
            }

            const Coordinates_Type & coordinates () const
            {
                return (static_cast< const Coordinates_Type & >(*this));
            }

        public:

            Vector & operator += (const Vector & other)
            {
                for (size_t index = 0; index < DIMENSION; index++)
                {
                    this->coordinates ()[index] += other.coordinates ()[index];
                }

                return (*this);
            }

        };

        template< typename NUMERIC_TYPE >
        class Vector< 0, NUMERIC_TYPE, true >
        {
            Vector() { }
        };

        template< typename NUMERIC_TYPE >
        class Vector< 2, NUMERIC_TYPE > : public Vector< 2, NUMERIC_TYPE, false >
        {
        public:

            typedef Vector< 2, NUMERIC_TYPE, false > Parent;
            typedef Parent                           Coordinates_Type;
            typedef NUMERIC_TYPE                     Numeric_Type;
            static  const size_t                     dimension = 2;

            using Coordinates_Type::X;
            using Coordinates_Type::Y;

        public:

            Vector()
            {
            }

            Vector(const Vector & other) : Parent(other)
            {
            }

            Vector(const Numeric_Type & given_x, const Numeric_Type & given_y)
            {
                this->values[X] = given_x;
                this->values[Y] = given_y;
            }

            Vector(const Numeric_Type (& given_values)[dimension]) : Parent(given_values)
            {
            }

            Vector(const Coordinates_Type & given_Coordinates) : Parent(given_Coordinates)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Vector(const OTHER_NUMERIC_TYPE (& given_values)[dimension]) : Parent(given_values)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Vector(const Vector< dimension, OTHER_NUMERIC_TYPE > & other) : Parent(other)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Vector(const Coordinates< dimension, OTHER_NUMERIC_TYPE > & given_Coordinates) : Parent(given_Coordinates)
            {
            }

        };

        typedef Vector< 1,     int > Vector1i;
        typedef Vector< 1,   float > Vector1f;
        typedef Vector< 1,  double > Vector1d;

        typedef Vector< 2,     int > Vector2i;
        typedef Vector< 2,   float > Vector2f;
        typedef Vector< 2,  double > Vector2d;

        typedef Vector< 3,     int > Vector3i;
        typedef Vector< 3,   float > Vector3f;
        typedef Vector< 3,  double > Vector3d;

        typedef Vector< 4,     int > Vector4i;
        typedef Vector< 4,   float > Vector4f;
        typedef Vector< 4,  double > Vector4d;

        typedef Vector< 1,  int8_t > Vector1i8;
        typedef Vector< 1, int16_t > Vector1i16;
        typedef Vector< 1, int32_t > Vector1i32;
        typedef Vector< 1, int64_t > Vector1i64;

        typedef Vector< 2,  int8_t > Vector2i8;
        typedef Vector< 2, int16_t > Vector2i16;
        typedef Vector< 2, int32_t > Vector2i32;
        typedef Vector< 2, int64_t > Vector2i64;

        typedef Vector< 3,  int8_t > Vector3i8;
        typedef Vector< 3, int16_t > Vector3i16;
        typedef Vector< 3, int32_t > Vector3i32;
        typedef Vector< 3, int64_t > Vector3i64;

        typedef Vector< 4,  int8_t > Vector4i8;
        typedef Vector< 4, int16_t > Vector4i16;
        typedef Vector< 4, int32_t > Vector4i32;
        typedef Vector< 4, int64_t > Vector4i64;

    }

#endif
