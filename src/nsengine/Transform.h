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

		void setPosition(rend::vec3);
		rend::vec3 getPosition();

		void Move(rend::vec3);

		void setScale(rend::vec3);
		rend::vec3 getScale();

		rend::mat4 Model();
		
	private:
		rend::vec3 rotation;
		rend::vec3 position;
		rend::vec3 scale;
	};
}