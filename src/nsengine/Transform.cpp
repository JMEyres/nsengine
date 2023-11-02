#include "Transform.h"
#include <iostream>

namespace nsengine
{
	void Transform::Rotate(rend::vec3 angle)
	{
		rotation = angle;
		//std::cout << rotation.y << std::endl;
		mat = rend::rotate_xyz(mat, rotation);
	}

	rend::mat4 Transform::Model()
	{
		mat = rend::translate(mat, position);
		return mat;
	}
}