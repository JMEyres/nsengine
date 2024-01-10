#include "Transform.h"
#include <iostream>

namespace nsengine
{
	Transform::Transform() :
		scale(1, 1, 1)
	{}

	void Transform::setRotation(rend::vec3 _angle)
	{
		rotation = _angle; // set this to be in degrees just in case
	}

	rend::vec3 Transform::getRotation()
	{
		return rotation;
	}

	void Transform::Rotate(float x, float y, float z)
	{
		rotation += rend::vec3 (x,y,z);

	}

	void Transform::setPosition(rend::vec3 _pos)
	{
		position = _pos;
	}

	void Transform::Move(rend::vec3 movement)
	{
		position += movement;
	}

	rend::vec3 Transform::getPosition()
	{
		return position;
	}

	void Transform::setScale(rend::vec3 _scale)
	{
		scale = _scale;
	}

	rend::vec3 Transform::getScale()
	{
		return scale;
	}

	rend::vec3 Transform::getForward(rend::vec3 movement)
	{
		rend::vec3 fwd = Model() * rend::vec4(movement, 0);
		fwd = rend::normalize(fwd);
		return fwd;
	}

	rend::vec3 Transform::getRight(rend::vec3 movement)
	{
		rend::vec3 fwd = Model() * rend::vec4(movement, 0);
		fwd = rend::normalize(fwd);
		rend::vec3 right = rend::cross(fwd, rend::vec3(0, 1, 0));
		right = rend::normalize(right);
		return right;
	}

	rend::vec3 Transform::getUp(rend::vec3 movement)
	{
		rend::quat quat(rotation);
		return quat * rend::vec3(0, 1, 0);
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