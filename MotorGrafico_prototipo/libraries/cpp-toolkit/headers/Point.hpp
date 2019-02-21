
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  POINT                                                                      *
 *  Copyright © 2013+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_POINT_HEADER
#define TOOLKIT_POINT_HEADER

    #include "Coordinates.hpp"

    namespace toolkit
    {

        template< size_t DIMENSION, typename NUMERIC_TYPE, bool SPECIALIZATION = true >
        class Point : public Coordinates< DIMENSION, NUMERIC_TYPE >
        {
        public:

            typedef Coordinates< DIMENSION, NUMERIC_TYPE > Coordinates_Type;
            typedef Coordinates_Type                       Parent;
            typedef NUMERIC_TYPE                           Numeric_Type;
            static  const size_t                           dimension = DIMENSION;

        public:

            Point()
            {
            }

            Point(const Point & other) : Parent(other)
            {
            }

            Point(const Numeric_Type (& given_values)[dimension]) : Parent(given_values)
            {
            }

            Point(const Coordinates_Type & given_Coordinates) : Parent(given_Coordinates)
            {
            }

            Point(const Matrix< 1, DIMENSION, Numeric_Type > & matrix) : Parent(reinterpret_cast< const Point & >(matrix))
            {
            }

            Point(const Matrix< DIMENSION, 1, Numeric_Type > & matrix) : Parent(reinterpret_cast< const Point & >(matrix))
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Point(const OTHER_NUMERIC_TYPE (& given_values)[dimension]) : Parent(given_values)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Point(const Point< dimension, OTHER_NUMERIC_TYPE > & other) : Parent(other)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Point(const Coordinates< dimension, OTHER_NUMERIC_TYPE > & given_Coordinates) : Parent(given_Coordinates)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Point(const Matrix< 1, DIMENSION, OTHER_NUMERIC_TYPE > & matrix) : Parent(reinterpret_cast< const OTHER_NUMERIC_TYPE (&) [DIMENSION] >(matrix))
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Point(const Matrix< DIMENSION, 1, OTHER_NUMERIC_TYPE > & matrix) : Parent(reinterpret_cast< const OTHER_NUMERIC_TYPE (&) [DIMENSION] >(matrix))
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

        };

        template< typename NUMERIC_TYPE >
        class Point< 0, NUMERIC_TYPE, true >
        {
            Point() { }
        };

        typedef Point< 1,     int > Point1i;
        typedef Point< 1,   float > Point1f;
        typedef Point< 1,  double > Point1d;

        typedef Point< 2,     int > Point2i;
        typedef Point< 2,   float > Point2f;
        typedef Point< 2,  double > Point2d;

        typedef Point< 3,     int > Point3i;
        typedef Point< 3,   float > Point3f;
        typedef Point< 3,  double > Point3d;

        typedef Point< 4,     int > Point4i;
        typedef Point< 4,   float > Point4f;
        typedef Point< 4,  double > Point4d;

        typedef Point< 1,  int8_t > Point1i8;
        typedef Point< 1, int16_t > Point1i16;
        typedef Point< 1, int32_t > Point1i32;
        typedef Point< 1, int64_t > Point1i64;

        typedef Point< 2,  int8_t > Point2i8;
        typedef Point< 2, int16_t > Point2i16;
        typedef Point< 2, int32_t > Point2i32;
        typedef Point< 2, int64_t > Point2i64;

        typedef Point< 3,  int8_t > Point3i8;
        typedef Point< 3, int16_t > Point3i16;
        typedef Point< 3, int32_t > Point3i32;
        typedef Point< 3, int64_t > Point3i64;

        typedef Point< 4,  int8_t > Point4i8;
        typedef Point< 4, int16_t > Point4i16;
        typedef Point< 4, int32_t > Point4i32;
        typedef Point< 4, int64_t > Point4i64;

    }

#endif
