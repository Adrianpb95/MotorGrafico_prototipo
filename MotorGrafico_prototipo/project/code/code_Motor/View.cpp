/*	
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "View.hpp"
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr
#include <SFML/OpenGL.hpp>


////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
    View::View(const string & name, int width, int height)    
		:
		window(new Window(VideoMode(width, height), name, Style::Default, ContextSettings(32)))
    {	
		//Inicializacion del glew despues de crear la ventana
		GLenum glew_initialization =  glewInit ();
		assert(glew_initialization == GLEW_OK);

		window->setVerticalSyncEnabled(true);		
		
		//Creacion de los elementos de la escena
		camera.reset(new Camera());		
		
		//Configuracion de elementos de OpenGL
        glEnable (GL_DEPTH_TEST);
        glEnable (GL_CULL_FACE);

		//Configuracion de la ventana
        resize (width, height);
    }   

    void View::resize (int new_width, int new_height)
    {
        width  = new_width;
        height = new_height;		

        camera->set_ratio (float(width) / height);

		for (auto & mat : materials)
		{
			mat.second->use();
			glm::mat4 projection_matrix = camera->get_projection();
			glUniformMatrix4fv(mat.second->get_projection_id(), 1, GL_FALSE, glm::value_ptr(projection_matrix));
		}
		
        glViewport (0, 0, width, height);		
    }
}
