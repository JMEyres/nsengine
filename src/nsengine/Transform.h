#pragma once
#include "Component.h"
#include <rend/rend.h>
#include <rend/glm/glm.hpp>
#include <memory>

namespace nsengine
{
	struct Transform : Component
	{
	public:
		void setRotation(rend::vec3);
		void setPosition(rend::vec3);
		void setScale(rend::vec3);
		rend::mat4 Model();
		
	private:
		rend::vec3 position;
		rend::vec3 rotation;
		rend::vec3 scale = rend::vec3(1.0f, 1.0f, 1.0f);
	};
}