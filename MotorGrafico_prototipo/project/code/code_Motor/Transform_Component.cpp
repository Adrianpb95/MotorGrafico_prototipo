/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
3 / 07 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Transform_Component.hpp"
#include "Entity.hpp"

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	void Transform_Component::run()
	{
		mesh->update(angle, scale, pos_x, pos_y, pos_z, rot_x, rot_y, rot_z);
	}

	void Transform_Component::parse(xml_node<> * transform_node, Entity * entity)
	{
		for (xml_attribute<> * attribute = transform_node->first_attribute(); attribute; attribute = attribute->next_attribute())
		{
			if		(string(attribute->name()) == "pos_x")  pos_x = stof(attribute->value());
			else if (string(attribute->name()) == "pos_y")  pos_y = stof(attribute->value());
			else if (string(attribute->name()) == "pos_z")	pos_z = stof(attribute->value());
			else if (string(attribute->name()) == "rot_x")	rot_x = stof(attribute->value());
			else if (string(attribute->name()) == "rot_y")	rot_y = stof(attribute->value());
			else if (string(attribute->name()) == "rot_z")	rot_z = stof(attribute->value());
			else if (string(attribute->name()) == "angle")	angle = stof(attribute->value());
			else if (string(attribute->name()) == "scale")	scale = stof(attribute->value());
		}
	}
}