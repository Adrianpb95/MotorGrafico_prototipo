
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  COORDINATES                                                                *
 *  Copyright © 2012+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_COORDINATES_HEADER
#define TOOLKIT_COORDINATES_HEADER

    #include <limits>
    #include "Matrix.hpp"   
    #include "Algorithms.hpp"

    namespace toolkit
    {

        template< size_t DIMENSION, typename NUMERIC_TYPE, bool SPECIALIZATION = true >
        class Coordinates
        {
        public:

            enum
            {
                X, Y, Z, T
            };

            typedef NUMERIC_TYPE Numeric_Type;
            static  const size_t dimension = DIMENSION;

        public:

            static const Numeric_Type min_coordinate () { return (std::numeric_limits< Numeric_Type >::min ()); }
            static const Numeric_Type max_coordinate () { return (std::numeric_limits< Numeric_Type >::max ()); }

        protected:

            Numeric_Type values[DIMENSION];

        public:

            Coordinates()
            {
            }

            Coordinates(const Coordinates & other)
            {
                copy (other.get_values (), this->values);
            }

            Coordinates(const Numeric_Type (& given_values)[dimension])
            {
                copy (given_values, this->values);
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Coordinates(const OTHER_NUMERIC_TYPE (& given_values)[dimension])
            {
                transform (given_values, this->values, numeric_type_cast< OTHER_NUMERIC_TYPE >);
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Coordinates(const Coordinates< dimension, OTHER_NUMERIC_TYPE > & other)
            {
                transform (other.get_values (), this->values, numeric_type_cast< OTHER_NUMERIC_TYPE >);
            }

        public:

            Numeric_Type (& get_values ())[dimension]
            {
                return (values);
            }

            const Numeric_Type (& get_values () const)[dimension]
            {
                return (values);
            }

        public:

            Coordinates & operator = (const Numeric_Type (& given_values)[dimension])
            {
                copy (given_values, this->values);
                return (*this);
            }

            Coordinates & operator = (const Coordinates & other)
            {
                copy (other.values, this->values);
                return (*this);
            }

        public:

            Numeric_Type & operator [] (size_t index)
            {
                return (values[index]);
            }

            const Numeric_Type & operator [] (size_t index) const
            {
                return (values[index]);
            }

        public:

            bool operator == (const Coordinates & other) const
            {
                return  (equal (other.values, this->values));
            }

            bool operator != (const Coordinates & other) const
            {
                return !(equal (other.values, this->values));
            }

        private:

            template< typename OTHER_NUMERIC_TYPE >
            static Numeric_Type numeric_type_cast (const OTHER_NUMERIC_TYPE & number)
            {
                return static_cast< Numeric_Type >(number);
            }

        public:

            operator const Matrix< 1, dimension, Numeric_Type > & () const
            {
                return (reinterpret_cast< const Matrix< 1, dimension, Numeric_Type > & >(*this));
            }

            operator const Matrix< dimension, 1, Numeric_Type > & () const
            {
                return (reinterpret_cast< const Matrix< dimension, 1, Numeric_Type > & >(*this));
            }

        };

        template< typename NUMERIC_TYPE >
        class Coordinates< 2, NUMERIC_TYPE, true > : public Coordinates< 2, NUMERIC_TYPE, false >
        {
        public:

            typedef Coordinates< 2, NUMERIC_TYPE, false > Parent;
            typedef NUMERIC_TYPE                          Numeric_Type;
            static  const size_t                          dimension = 2;

            using Parent::X;
            using Parent::Y;

        public:

            Coordinates()
            {
            }

            Coordinates(const Coordinates & other) : Parent(other)
            {
            }

            Coordinates(const Numeric_Type & given_x, const Numeric_Type & given_y)
            {
                this->values[X] = given_x;
                this->values[Y] = given_y;
            }

            Coordinates(const Numeric_Type (& given_values)[dimension]) : Parent(given_values)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Coordinates(const OTHER_NUMERIC_TYPE (& given_values)[dimension]) : Parent(given_values)
            {
            }

            template< typename OTHER_NUMERIC_TYPE >
            explicit Coordinates(const Coordinates< dimension, OTHER_NUMERIC_TYPE > & other) : Parent(other)
            {
            }

        public:

                  Numeric_Type & x ()       { return (this->values[X]); }
            const Numeric_Type & x () const { return (this->values[X]); }

                  Numeric_Type & y ()       { return (this->values[Y]); }
            const Numeric_Type & y () const { return (this->values[Y]); }

        };

    }

#endif
