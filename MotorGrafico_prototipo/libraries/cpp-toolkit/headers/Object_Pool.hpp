
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  OBJECT POOL                                                                *
 *                                                                             *
 *  Copyright © 2013+ Ángel Rodriguez Ballesteros                              *
 *                                                                             *
 *  Distributed under the Boost Software License, version  1.0                 *
 *  See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt                 *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef TOOLKIT_OBJECT_POOL_HEADER
#define	TOOLKIT_OBJECT_POOL_HEADER

    #include <new>
    #include <cassert>
    #include "types.hpp"

    namespace toolkit
    {

        // Hacer que haya una clase base común.
        // Hacer que el tamaño de object_buffer sea múltiplo del tamaño del registro del procesador.
        // Hacer que cada Object_Pool herede del Object_Pool con tamaño de object_buffer múltiplo del tamaño del registro del procesador.

        template< typename TYPE, size_t SEGMENT_SIZE = 1024 >
        class Object_Pool
        {
        public:

            typedef size_t          size_type;
            typedef TYPE            object_type;
            typedef object_type   * object_pointer;
            static  const size_type segment_size = SEGMENT_SIZE;

        private:

            struct                  element_type;
            typedef element_type  * element_pointer;
            struct                  segment_type;
            typedef segment_type  * segment_pointer;
            typedef byte            object_buffer[sizeof(object_type)];

        private:

            struct element_type
            {

                object_buffer   object_data;                    // This buffer is plain memory to avoid automatic constructors/destructors
                segment_pointer segment;                        // This pointer speeds up deallocation
                element_pointer next_free;                      // Pointer to the next free element
                element_pointer previous_free;                  // Pointer to the previous free element

               ~element_type()
                {
                    // If the next and the previous elements are null and this is not a singleton element,
                    // then this element has been left allocated and must be destructed:

                    if (next_free == previous_free && this != segment->first_free_element)
                    {
                        destruct ();
                    }
                }

                object_pointer object ()
                {
                    return (reinterpret_cast< object_pointer >(object_data));
                }

                void destruct ()
                {
                    object ()->~object_type ();
                }

            };

            struct segment_type
            {

                element_type    elements[segment_size];         // Elements array
                element_pointer first_free_element;             // Pointer to the first free element
                segment_pointer previous;                       // Pointer to the next segment along the list
                segment_pointer next;                           // Pointer to the previous segment along the list
                size_type       number_of_elements_used;        // Needed  to know when a  segment becomes void

                segment_type()
                {
                    // Initialize the free element list:

                    for (element_pointer element = elements, end = elements + segment_size; element != end; element++)
                    {
                        element->segment       = this;
                        element->previous_free = element - 1;
                        element->next_free     = element + 1;
                    }

                    // Mark both ends of the list:

                    elements[0].previous_free = elements[segment_size - 1].next_free = null;

                    // Initialize the pointers:

                    previous = next    = null;
                    first_free_element = elements;
                }

            };

        private:

            segment_pointer full_segments;
            segment_pointer free_segments;
            segment_pointer void_segments;

            size_type       number_of_void_segments;
            size_type       maximum_number_of_void_segments;

        public:

            Object_Pool(size_type desired_maximum_number_of_void_segments = 1)
            {
                full_segments = null;
                free_segments = null;
                void_segments = null;

                        number_of_void_segments = 0;
                maximum_number_of_void_segments = desired_maximum_number_of_void_segments;
            }

           ~Object_Pool()
            {
                assert(full_segments == null);
                assert(free_segments == null);

                free_all ();
            }

        public:

            object_pointer allocate ()
            {
                if (free_segments)
                {
                    // Take the first free object of the first free segment:

                    segment_pointer segment = free_segments;
                    element_pointer element = segment->first_free_element;

                    // Adjust the count of objects of the segment being used:

                    segment->number_of_elements_used++;

                    // Remove the element from the free element list and move the segment to
                    // the full segment list if necessary:

                    if ((segment->first_free_element = element->next_free) != null)
                    {
                         segment->first_free_element->previous_free = null;
                    }
                    else
                    {
                         unlink (segment, free_segments);
                         link   (segment, full_segments);
                    }

                    // An allocated element doesn't point to other elements:

                    element->next_free = element->previous_free = null;

                    return (element->object ());
                }
                else
                {
                    segment_pointer segment;

                    if (void_segments)
                    {
                        // If there is a void segment, we will take its first object so it won't be
                        // void anymore, then we can unlink it directly:

                        unlink (segment = void_segments, void_segments);
                    }
                    else
                    {
                        // If there're no free or void segments, a new segment must be allocated:

                        segment = new (std::nothrow) segment_type;

                        // If the segment could not be allocated we notify it on debug builds:

                        assert(segment);
                    }

                    if (segment)
                    {
                        // If there's a segment, we reserve its first object:

                        element_pointer element = segment->elements;

                        // Remove the element from the free element list and move the segment to
                        // the free segment list:

                        segment->number_of_elements_used           = 1;
                        segment->first_free_element                = element->next_free;
                        segment->first_free_element->previous_free = element->next_free = element->previous_free = null;

                        link (segment, free_segments);

                        return (element->object ());
                    }
                }

                // It was not possible allocating an object:

                assert (false);
                return (null );
            }

            object_pointer allocate_new ()
            {
                return (new (allocate ()) object_type());
            }

            void free (object_pointer object)
            {
                if (object)
                {
                    // Point to the element and to the segment:

                    element_pointer element = reinterpret_cast< element_pointer >(object);
                    segment_pointer segment = element->segment;

                    // Validate the input in debug builds:

                    assert(element >= segment->elements && element < segment->elements + segment_size);
                    assert(element->previous_free == element->next_free);

                    // Destruct the object:

                    element->destruct ();

                    // Adjust the count of objects of the segment being used:

                    segment->number_of_elements_used--;

                    if (segment->first_free_element)        // The segment is part of the free segments list
                    {
                        // Insert the element at the beginning of the free element list:

                        element->next_free          = segment->first_free_element;
                        segment->first_free_element = segment->first_free_element->previous_free = element;

                        // If the segment is now void, move it to the void segment list or delete it:

                        if (segment->number_of_elements_used == 0)
                        {
                            unlink (segment, free_segments);

                            if (number_of_void_segments < maximum_number_of_void_segments)
                            {
                                link (segment, void_segments);

                                number_of_void_segments++;
                            }
                            else
                            {
                                delete segment;
                            }
                        }
                    }
                    else                                    // The segment is part of the full segments list
                    {
                        // The element will be the first and only free element of the segment:

                        segment->first_free_element = element;

                        // The segment is part of the full segments list but, after freeing one
                        // object, it must be moved to the free segments list:

                        unlink (segment, full_segments);
                        link   (segment, free_segments);
                    }
                }
            }

            void free_all ()
            {
                delete_all (full_segments); full_segments = null;
                delete_all (free_segments); free_segments = null;
                delete_all (void_segments); void_segments = null;
            }

        private:

            static void link (segment_pointer segment, segment_pointer & list_root)
            {
                // The segment->previous and segment->next pointers are supposed to be unlinked (null).

                if (list_root)
                {
                    list_root->previous = segment;
                    segment->next = list_root;
                }

                // We link the segment at be beginning of the list:

                list_root = segment;
            }

            static void unlink (segment_pointer segment, segment_pointer & list_root)
            {
                if (segment == list_root)
                {
                    // The segment is the root node of the list.

                    if (segment->next)
                    {
                        // In this case the next node will be the first node:

                        segment->next->previous = null;
                        list_root   = segment->next;
                        segment->next = null;
                    }
                    else
                    {
                        // Removing a single node leaves the list empty:

                        list_root = null;
                    }
                }
                else
                {
                    // The segment is not the root node of the list.
                    // In this case it has a previous node which we can relink directly:

                    segment->previous->next = segment->next;

                    // If there's a next node we relink it:

                    if (segment->next)
                    {
                        segment->next->previous = segment->previous;
                    }

                    // Finally the links of the segment are cleared:

                    segment->previous = segment->next = null;
                }
            }

            static void delete_all (segment_pointer segment)
            {
                while (segment)
                {
                    segment_pointer next_segment = segment->next;

                    delete segment;

                    segment = next_segment;
                }
            }

        };

    }

#endif
