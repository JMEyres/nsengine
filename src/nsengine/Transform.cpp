#include "Transform.h"
#include <iostream>

namespace nsengine
{
	Transform::Transform() :
		scale(1, 1, 1)
	{}

	void Transform::setRotation(rend::vec3 _angle)
	{
		rotation = _angle;
	}

	void Transform::setPosition(rend::vec3 _pos)
	{
		position = _pos;
	}

	void Transform::setScale(rend::vec3 _scale)
	{
		scale = _scale;
	}

	void Transform::Move(rend::vec3 _movement)
	{
	
	}

	rend::mat4 Transform::Model()
	{
		rend::mat4 mat = rend::mat4(1.0f); // mat = matrix

		mat = rend::translate(mat, position); // set position of matrix

		mat = rend::rotate(mat, rend::radians(rotation.y), rend::vec3(0, 1, 0)); // set rotations, y first so it favours the y axis rotation because it is the msot commonly used
		mat = rend::rotate(mat, rend::radians(rotation.x), rend::vec3(1, 0, 0));
		mat = rend::rotate(mat, rend::radians(rotation.z), rend::vec3(0, 0, 1));

		mat = rend::scale(mat, scale); // scale matrix
		
		return mat; // return matrix
	}
}