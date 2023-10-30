#include "Transform.h"

namespace nsengine
{
	rend::mat4 Transform::Rotate(rend::mat4 mat, float angle, rend::vec3 axis)
	{
		mat = rend::rotate(mat, angle, axis);
		return mat;
	}

	void Transform::Model()
	{
	
	}
}