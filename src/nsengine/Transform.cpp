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

	void Transform::rotate(rend::vec3 rotate)
	{
		rotation += rotate;
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

	rend::vec3 Transform::getUp()
	{
		rend::quat quat(rotation);
		return quat * rend::vec3(0, 1, 0);
	}

	rend::vec3 Transform::getDown()
	{
		rend::quat quat(rotation);
		return quat * rend::vec3(0, -1, 0);
	}

	rend::vec3 Transform::getRight()
	{
		rend::quat quat(rotation);
		return quat * rend::vec3(1, 0, 0);
	}

	rend::vec3 Transform::getLeft()
	{
		rend::quat quat(rotation);
		return quat * rend::vec3(-1, 0, 0);
	}

	rend::vec3 Transform::getForward()
	{
		rend::quat quat(rotation);
		return quat * rend::vec3(0, 0, -1); // glm has -z forwards
	}

	rend::vec3 Transform::getBack()
	{
		rend::quat quat(rotation);
		return quat * rend::vec3(0, 0, 1);
	}


	rend::mat4 Transform::Model()
	{
		rend::mat4 mat = rend::mat4(1.0f); // mat = matrix

		mat = rend::translate(mat, position); // set position of matrix

		mat = rend::rotate(mat, rend::radians(rotation.y), rend::vec3(0, 1, 0)); // set rotations, y first so it favours the y axis rotation because it is the most commonly used
		mat = rend::rotate(mat, rend::radians(rotation.x), rend::vec3(1, 0, 0));
		mat = rend::rotate(mat, rend::radians(rotation.z), rend::vec3(0, 0, 1));

		mat = rend::scale(mat, scale); // scale matrix
		
		return mat; // return matrix
	}
}