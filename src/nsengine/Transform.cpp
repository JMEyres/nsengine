#include "Transform.h"
#include <iostream>

namespace nsengine
{
	Transform::Transform() :
		scale(1, 1, 1)
	{}

	void Transform::SetRotation(rend::vec3 _angle)
	{
		rotation = _angle; // set this to be in degrees just in case
	}

	rend::vec3 Transform::GetRotation()
	{
		return rotation;
	}

	void Transform::Rotate(float x, float y, float z)
	{
		rotation += rend::vec3(x, y, z);
	}

	void Transform::SetPosition(rend::vec3 _pos)
	{
		position = _pos;
	}

	void Transform::Move(float x, float y, float z)
	{
		rend::vec3 movement = Model() * rend::vec4(x, y, z, 0);
		position += movement;
	}

	rend::vec3 Transform::GetPosition()
	{
		return position;
	}

	void Transform::SetScale(rend::vec3 _scale)
	{
		scale = _scale;
	}

	rend::vec3 Transform::GetScale()
	{
		return scale;
	}

	rend::mat4 Transform::Model()
	{
		mat = rend::mat4(1.0f); // mat = matrix

		mat = rend::translate(mat, position); // set position of matrix

		mat = rend::rotate(mat, rend::radians(rotation.y), rend::vec3(0, 1, 0)); // set rotations, y first so it favours the y axis rotation because it is the most commonly used
		mat = rend::rotate(mat, rend::radians(rotation.x), rend::vec3(1, 0, 0));
		mat = rend::rotate(mat, rend::radians(rotation.z), rend::vec3(0, 0, 1));

		mat = rend::scale(mat, scale); // scale matrix
		
		return mat; // return matrix
	}
}