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
		//rend::vec3 orientation = Model() * rend::vec4(x, y, z, 0);
		//rotation += orientation;
		rotation += rend::vec3(x, y, z);
	}

	void Transform::setPosition(rend::vec3 _pos)
	{
		position = _pos;
	}

	void Transform::Move(float x, float y, float z)
	{
		rend::vec3 movement = Model() * rend::vec4(x, y, z, 0);
		//rend::vec3 movement = rend::vec3(0,0,-1) * getRight();
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

	rend::vec3 Transform::getForward()
	{
		rend::vec3 forward;
		forward.x = glm::cos(getRotation().x) * glm::sin(getRotation().y);
		forward.y = -glm::sin(getRotation().x);
		forward.z = glm::cos(getRotation().x) * glm::cos(getRotation().y);
		return forward;
	}

	rend::vec3 Transform::getRight()
	{
		rend::vec3 right;
		right.x = glm::cos(getRotation().y);
		right.y = 0;
		right.z = -glm::sin(getRotation().y);
		return right;
	}

	rend::vec3 Transform::getUp()
	{
		rend::vec3 up;
		up = glm::cross(getForward(), getRight());
		return up;
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