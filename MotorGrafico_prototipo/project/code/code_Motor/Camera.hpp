
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on april of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
EDITED BY:
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/

#ifndef CAMERA_HEADER
#define CAMERA_HEADER


    #include <glm/glm.hpp>							// vec3, vec4, ivec4, mat4	
    #include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
    #include <glm/gtc/type_ptr.hpp>                 // value_ptr

    namespace example
    {

        class Camera
        {
            typedef glm::vec4 Point;           

        private:

            float  fov;
            float  near_z;
            float  far_z;
            float  ratio;

            Point  location;
            Point  target;

        public:

            Camera(float ratio = 1.f)
            {
                reset (60.f, 0.1f, 100.f, ratio);
            }

            Camera(float near_z, float far_z, float ratio = 1.f)
            {
                reset (60.f, near_z, far_z, ratio);
            }

            Camera(float fov, float near_z, float far_z, float ratio)
            {
                reset (fov, near_z, far_z, ratio);
            }

        public:

            float          get_fov       () const { return fov;    }
            float          get_near_z    () const { return near_z; }
            float          get_far_z     () const { return far_z;  }
            float          get_ratio     () const { return ratio;  }

            const Point  & get_location  () const { return location; }
            const Point  & get_target    () const { return target;   }

			////////////////////////////////////////////////////////////
			/// \brief	Devuelve el vector direccion de la camara
			////////////////////////////////////////////////////////////
			const Point  get_direction () const { return glm::normalize (target - location); }

        public:

            void set_fov      (float new_fov   ) { fov    = new_fov;    }
            void set_near_z   (float new_near_z) { near_z = new_near_z; }
            void set_far_z    (float new_far_z ) { far_z  = new_far_z;  }
            void set_ratio    (float new_ratio ) { ratio  = new_ratio;  }

            void set_location (float x, float y, float z) { location[0] = x; location[1] = y; location[2] = z; }
            void set_target   (float x, float y, float z) { target  [0] = x; target  [1] = y; target  [2] = z; }

            void reset (float new_fov, float new_near_z, float new_far_z, float new_ratio)
            {
                set_fov      (new_fov   );
                set_near_z   (new_near_z);
                set_far_z    (new_far_z );
                set_ratio    (new_ratio );
                set_location (0.f,  0.f,  0.f);
                set_target   (0.f,  0.f, -1.f);
            }

        public:

            void move (const glm::vec3 & translation)
            {
                location += glm::vec4 (translation, 1.f);
                target   += glm::vec4 (translation, 1.f);
            }

			void move(const glm::vec4 & translation)
			{
				location += glm::vec4(translation);
				target += glm::vec4(translation);
			}

            void rotate (const glm::mat4 & rotation)
            {
                target = location + rotation * (target - location);
            }

        public:

            glm::mat4 get_projection () const
            {
                return glm::perspective (fov, ratio, near_z, far_z);
            }

            glm::mat4 get_model_view () const
            {
                return glm::lookAt
                (
                    glm::vec3(location[0], location[1], location[2]),
                    glm::vec3(target  [0], target  [1], target  [2]),
                    glm::vec3(       0.0f,        1.0f,        0.0f)
                );
            }

        };

    }

#endif
