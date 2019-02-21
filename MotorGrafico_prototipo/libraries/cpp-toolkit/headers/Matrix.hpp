
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  MATRIX                                                                     *
 *  Copyright © 2012+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_MATRIX_HEADER
#define TOOLKIT_MATRIX_HEADER

    #include "Algorithms.hpp"

    namespace toolkit
    {

        template< size_t M, size_t N, typename NUMERIC_TYPE >
        class Matrix
        {
        public:

            typedef NUMERIC_TYPE Numeric_Type;
            static  const size_t number_of_rows    = M;
            static  const size_t number_of_columns = N;

        public:

            class Row
            {
            private:

                Numeric_Type * const values;

            public:

                Row(Matrix * const given_matrix, const size_t row_index)
                :
                    values(given_matrix->values + row_index * N)
                {
                }

                Numeric_Type & operator [] (const size_t column_index)
                {
                    return (values[column_index]);
                }

                const Numeric_Type & operator [] (const size_t column_index) const
                {
                    return (values[column_index]);
                }

                Row & operator = (const Row & other)
                {
                    for (size_t index = 0; index < N; ++index)
                    {
                        this->values[index] = other.values[index];
                    }

                    return (*this);
                }

                template< size_t OTHER_N >
                Row & operator = (const typename Matrix< N, OTHER_N, Numeric_Type >::Column & other_column)
                {
                    for (size_t index = 0; index < N; ++index)
                    {
                        this->values[index] = other_column.values[index * N];
                    }

                    return (*this);
                }

            };

            class Column
            {
            private:

                Numeric_Type  * const values;

            public:

                Column(Matrix * const given_matrix, const size_t column_index)
                :
                    values(given_matrix->values + column_index)
                {
                }

                Numeric_Type & operator [] (const size_t row_index)
                {
                    return (values[row_index * N]);
                }

                const Numeric_Type & operator [] (const size_t row_index) const
                {
                    return (values[row_index * N]);
                }

                Column & operator = (const Column & other)
                {
                    for (size_t index = 0; index < M; ++index)
                    {
                        this->values[index * N] = other.values[index * N];
                    }

                    return (*this);
                }

                template< size_t OTHER_M >
                Column & operator = (const typename Matrix< OTHER_M, M, Numeric_Type >::Row & other_row)
                {
                    for (size_t index = 0; index < M; ++index)
                    {
                        this->values[index * N] = other_row.values[index];
                    }

                    return (*this);
                }

            };

        public:

            static const Matrix identity;

        public:

            Numeric_Type values[M * N];

        public:

            Matrix()
            {
            }

        private:

            enum Identity
            {
                IDENTITY
            };

            Matrix(const Identity & )
            {
                fill (values, Numeric_Type(0));

                for (size_t offset = 0; offset < M * N; offset += N + 1)
                {
                    values[offset] = Numeric_Type(1);
                }
            }

        public:

            Row row (const size_t row_index)
            {
                return Row(this, row_index);
            }

            const Row row (const size_t row_index) const
            {
                return Row(this, row_index);
            }

            Column column (const size_t column_index)
            {
                return Column(this, column_index);
            }

            const Column column (const size_t column_index) const
            {
                return Column(this, column_index);
            }

            Row operator [] (const size_t row_index)
            {
                return Row(this, row_index);
            }

            const Row operator [] (const size_t row_index) const
            {
                return Row(const_cast< Matrix * >(this), row_index);
            }

        public:

            template< size_t P >
            const Matrix< M, P, NUMERIC_TYPE > operator * (const Matrix< N, P, NUMERIC_TYPE > & other) const
            {
                Matrix< M, P, NUMERIC_TYPE > result;

                for (size_t r = M; r-- > 0; )
                {
                    for (size_t c = P; c-- > 0; )
                    {
                        NUMERIC_TYPE total = 0;

                        for (size_t index = N; index-- > 0; )
                        {
                            total += (*this)[r][index] * other[index][c];
                        }

                        result[r][c] = total;
                    }
                }

                return (result);
            }

        };

        template< size_t M, size_t N, typename NUMERIC_TYPE >
        const Matrix< M, N, NUMERIC_TYPE > Matrix< M, N, NUMERIC_TYPE >::identity(IDENTITY);

        template< typename  NUMERIC_TYPE >
        class Matrix< 0, 0, NUMERIC_TYPE >
        {
            Matrix() { }
        };

        typedef Matrix< 2, 2,    int > Matrix22i;
        typedef Matrix< 2, 2,  float > Matrix22f;
        typedef Matrix< 2, 2, double > Matrix22d;

        typedef Matrix< 3, 3,    int > Matrix33i;
        typedef Matrix< 3, 3,  float > Matrix33f;
        typedef Matrix< 3, 3, double > Matrix33d;

        typedef Matrix< 4, 4,    int > Matrix44i;
        typedef Matrix< 4, 4,  float > Matrix44f;
        typedef Matrix< 4, 4, double > Matrix44d;

        typedef Matrix< 2, 1,    int > Matrix21i;
        typedef Matrix< 2, 1,  float > Matrix21f;
        typedef Matrix< 2, 1, double > Matrix21d;

        typedef Matrix< 3, 1,    int > Matrix31i;
        typedef Matrix< 3, 1,  float > Matrix31f;
        typedef Matrix< 3, 1, double > Matrix31d;

        typedef Matrix< 4, 1,    int > Matrix41i;
        typedef Matrix< 4, 1,  float > Matrix41f;
        typedef Matrix< 4, 1, double > Matrix41d;

    }

#endif
