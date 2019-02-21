
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  TRANSFORMATION                                                             *
 *  Copyright © 2014+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_TRANSFORMATION_HEADER
#define TOOLKIT_TRANSFORMATION_HEADER

    #include <Matrix.hpp>

    namespace toolkit
    {

        template< size_t DIMENSION, typename NUMERIC_TYPE >
        class Transformation
        {
        public:

            typedef toolkit::Matrix< DIMENSION + 1, DIMENSION + 1, NUMERIC_TYPE > Matrix;

        protected:

            Matrix matrix;

        public:

            Transformation()
            :
                matrix(Matrix::identity)
            {
            }

            Transformation(const Matrix & matrix)
            :
                matrix(matrix)
            {
            }

        public:

            Transformation operator * (const Transformation & other) const
            {
                return (this->matrix * other.matrix);
            }

            operator const Matrix & () const
            {
                return (matrix);
            }

        };

        typedef Transformation< 2, int    > Transformation2i;
        typedef Transformation< 2, float  > Transformation2f;
        typedef Transformation< 2, double > Transformation2d;

        typedef Transformation< 3, int    > Transformation3i;
        typedef Transformation< 3, float  > Transformation3f;
        typedef Transformation< 3, double > Transformation3d;

    }

#endif
