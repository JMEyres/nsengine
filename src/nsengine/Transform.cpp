#include "Transform.h"
#include <iostream>

namespace nsengine
{
	void Transform::setRotation(rend::vec3 _angle)
	{
		rotation += _angle;
	}

	void Transform::setPosition(rend::vec3 _pos)
	{
		position = _pos;
	}

	void Transform::setScale(rend::vec3 _scale)
	{
		scale = _scale;
	}

	rend::mat4 Transform::Model()
	{
		rend::mat4 mat = rend::mat4(1.0f);
		mat = rend::scale(mat, scale);
		mat = rend::translate(mat, position);

		mat = rend::rotate(mat, rotation.x, rend::vec3(1, 0, 0));
		mat = rend::rotate(mat, rotation.y, rend::vec3(0, 1, 0));
		mat = rend::rotate(mat, rotation.z, rend::vec3(0, 0, 1));

		return mat;
	}
}