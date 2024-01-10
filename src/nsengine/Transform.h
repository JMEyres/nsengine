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
		void Move(float x, float y, float z);

		void setScale(rend::vec3);
		rend::vec3 getScale();

		rend::mat4 Model();
	private:
		rend::mat4 mat;
		rend::vec3 rotation;
		rend::vec3 position;
		rend::vec3 scale;
	};
}