
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  ALGORITHMS                                                                 *
 *  Copyright © 2011+ Ángel Rodríguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_ALGORITHMS_HEADER
#define TOOLKIT_ALGORITHMS_HEADER

    #include "types.hpp"

    namespace toolkit
    {

        // ------------------------------ COPY ------------------------------ //

        template< typename TYPE, size_t SIZE >
        inline void copy (const TYPE (& source)[SIZE], TYPE (& destination)[SIZE])
        {
            for (size_t index = 0; index < SIZE; ++index)
            {
                destination[index] = source[index];
            }
        }

        template< typename TYPE >
        inline void copy (const TYPE (& source)[1u], TYPE (& destination)[1u])
        {
            *destination = *source;
        }

        template< typename TYPE >
        inline void copy (const TYPE (& source)[2u], TYPE (& destination)[2u])
        {
            destination[0] = source[0];
            destination[1] = source[1];
        }

        template< typename TYPE >
        inline void copy (const TYPE (& source)[3u], TYPE (& destination)[3u])
        {
            destination[0] = source[0];
            destination[1] = source[1];
            destination[2] = source[2];
        }

        template< typename TYPE >
        inline void copy (const TYPE (& source)[4u], TYPE (& destination)[4u])
        {
            destination[0] = source[0];
            destination[1] = source[1];
            destination[2] = source[2];
            destination[3] = source[3];
        }


        // ------------------------------ FILL ------------------------------ //

        template< typename TYPE, typename RELATED_TYPE, size_t SIZE >
        inline void fill (TYPE (& destination)[SIZE], const RELATED_TYPE & value)
        {
            for (size_t index = 0; index < SIZE; ++index)
            {
                destination[index] = value;
            }
        }

        template< typename TYPE, typename RELATED_TYPE >
        inline void fill (TYPE (& destination)[1u], const RELATED_TYPE & value)
        {
            *destination = value;
        }

        template< typename TYPE, typename RELATED_TYPE >
        inline void fill (TYPE (& destination)[2u], const RELATED_TYPE & value)
        {
            destination[0] = destination[1] = value;
        }

        template< typename TYPE, typename RELATED_TYPE >
        inline void fill (TYPE (& destination)[3u], const RELATED_TYPE & value)
        {
            destination[0] = destination[1] = destination[2] = value;
        }

        template< typename TYPE, typename RELATED_TYPE >
        inline void fill (TYPE (& destination)[4u], const RELATED_TYPE & value)
        {
            destination[0] = destination[1] = destination[2] = destination[3] = value;
        }


        // ---------------------------- TRANSFORM --------------------------- //

        template< typename OPERAND_TYPE, typename RESULT_TYPE, typename UNARY_OPERATOR, size_t SIZE >
        inline void transform (const OPERAND_TYPE (& operand)[SIZE], RESULT_TYPE (& result)[SIZE], UNARY_OPERATOR unary_operator)
        {
            for (size_t index = 0; index < SIZE; ++index)
            {
                result[index] = unary_operator (operand[index]);
            }
        }

        template< typename OPERAND_TYPE, typename RESULT_TYPE, typename UNARY_OPERATOR >
        inline void transform (const OPERAND_TYPE (& operand)[1u], RESULT_TYPE (& result)[1u], UNARY_OPERATOR unary_operator)
        {
            result[0] = unary_operator (operand[0]);
        }

        template< typename OPERAND_TYPE, typename RESULT_TYPE, typename UNARY_OPERATOR >
        inline void transform (const OPERAND_TYPE (& operand)[2u], RESULT_TYPE (& result)[2u], UNARY_OPERATOR unary_operator)
        {
            result[0] = unary_operator (operand[0]);
            result[1] = unary_operator (operand[1]);
        }

        template< typename OPERAND_TYPE, typename RESULT_TYPE, typename UNARY_OPERATOR >
        inline void transform (const OPERAND_TYPE (& operand)[3u], RESULT_TYPE (& result)[3u], UNARY_OPERATOR unary_operator)
        {
            result[0] = unary_operator (operand[0]);
            result[1] = unary_operator (operand[1]);
            result[2] = unary_operator (operand[2]);
        }

        template< typename OPERAND_TYPE, typename RESULT_TYPE, typename UNARY_OPERATOR >
        inline void transform (const OPERAND_TYPE (& operand)[4u], RESULT_TYPE (& result)[4u], UNARY_OPERATOR unary_operator)
        {
            result[0] = unary_operator (operand[0]);
            result[1] = unary_operator (operand[1]);
            result[2] = unary_operator (operand[2]);
            result[3] = unary_operator (operand[3]);
        }


        // ------------------------------ EQUAL ----------------------------- //

        template< typename TYPE, size_t SIZE >
        inline bool equal (const TYPE (& a)[SIZE], const TYPE (& b)[SIZE])
        {
            for (size_t index = 0; index < SIZE; ++index)
            {
                if (a[index] != b[index])
                {
                    return (false);
                }
            }

            return (true);
        }

        template< typename TYPE >
        inline bool equal (const TYPE (& a)[1u], const TYPE (& b)[1u])
        {
            return (a[0] == b[0]);
        }

        template< typename TYPE >
        inline bool equal (const TYPE (& a)[2u], const TYPE (& b)[2u])
        {
            return (a[0] == b[0] && a[1] == b[1]);
        }

        template< typename TYPE >
        inline bool equal (const TYPE (& a)[3u], const TYPE (& b)[3u])
        {
            return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2]);
        }

        template< typename TYPE >
        inline bool equal (const TYPE (& a)[4u], const TYPE (& b)[4u])
        {
            return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3]);
        }

    }

#endif
