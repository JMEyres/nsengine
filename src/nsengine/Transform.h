#pragma once
#include "Component.h"
#include <rend/rend.h>

namespace nsengine
{
	struct Transform : public Component
	{
		Transform();

		void setRotation(rend::vec3);
		rend::vec3 getRotation();
		void Rotate(float x, float y, float z);

		void setPosition(rend::vec3);
		rend::vec3 getPosition();
		void Move(rend::vec3);
		void setSpeed(float);

		void setScale(rend::vec3);
		rend::vec3 getScale();

		rend::mat4 Model();

		rend::vec3 getForward(rend::vec3 movement);
		rend::vec3 getRight(rend::vec3 movement);
		rend::vec3 getUp(rend::vec3 movement);

	private:
		rend::mat4 mat;
		rend::vec3 rotation;
		rend::vec3 position;
		rend::vec3 scale;
		//rend::vec3 fwd;
		//rend::vec3 right;
		//rend::vec3 up;
	};
}