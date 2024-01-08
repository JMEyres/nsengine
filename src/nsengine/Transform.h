#pragma once
#include "Component.h"
#include <rend/rend.h>

namespace nsengine
{
	struct Transform : public Component
	{
		Transform();

		void setRotation(rend::vec3);
		void rotate(float x, float y, float z);

		void setPosition(rend::vec3);
		glm::vec3 getPosition();
		void Move(rend::vec3);

		void setScale(rend::vec3);

		rend::mat4 Model();
		rend::vec3 rotation;
		
	private:
		rend::vec3 position;
		rend::vec3 scale;
	};
}