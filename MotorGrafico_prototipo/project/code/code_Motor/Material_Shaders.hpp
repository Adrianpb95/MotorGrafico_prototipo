
/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/


#ifndef MATERIAL_SHADERS_HEADER
#define MATERIAL_SHADERS_HEADER

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>


////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	//CONTENEDOR DE SHADERS


	//Shaders de textura y luz
	const std::string vertex_shader_code =

		"#version 330\n"
		""
		"struct Light"
		"{"
		"    vec4 position;"
		"    vec3 color;"
		"	 float ambient_intensity;"
		"	 float diffuse_intensity;"
		"};"
		""
		"uniform Light light;"
		""
		"uniform mat4 model_view_matrix;"
		"uniform mat4 projection_matrix;"
		"uniform mat4     normal_matrix;"
		""
		"out vec2 texture_uv;"
		"out float light_intensity;"
		"out float light_ambient_intensity;"
		"out float light_diffuse_intensity;"
		"out vec3 light_color;"
		""
		"layout (location = 0) in vec3 vertex_coordinates;"
		"layout (location = 1) in vec2 vertex_texture_uv;"
		"layout (location = 2) in vec3 vertex_normal;"
		""
		"void main()"
		"{"
		"    vec4  normal   = normal_matrix * vec4(vertex_normal, 1.0);"
		"    vec4  position = model_view_matrix * vec4(vertex_coordinates, 1.0);"
		""
		"    vec4  light_direction = light.position - position;"
		"    light_intensity = light.diffuse_intensity * max (dot (normalize (normal.xyz), normalize (light_direction.xyz)), 0.0);"
		""
		"	 light_ambient_intensity = light.ambient_intensity;"
		"	 light_diffuse_intensity = light.diffuse_intensity;"
		"	 light_color = light.color;"
		"    texture_uv  = vertex_texture_uv;"
		"    gl_Position = projection_matrix * position;"
		"}";

	const std::string fragment_shader_code =
		"#version 330\n"
		""
		"uniform sampler2D sampler2d;"
		""
		"in  vec2  texture_uv;"
		"in  float light_intensity;"
		"in  float light_ambient_intensity;"
		"in  float light_diffuse_intensity;"
		"in  vec3  light_color;"
		""
		"out vec4  fragment_color;"
		""
		"void main()"
		"{"
		"    fragment_color = vec4(light_ambient_intensity * texture (sampler2d, texture_uv.st).rgb, 1.0) + vec4(light_diffuse_intensity * light_color * light_intensity * texture (sampler2d, texture_uv.st).rgb, 1.0);"
		"}";	
}
#endif