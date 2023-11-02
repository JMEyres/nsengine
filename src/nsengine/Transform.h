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
		void Rotate(rend::vec3);
		rend::mat4 Model();
		
	private:
		rend::vec3 position = rend::vec3(0.0f, 0.0f, -10.0f);
		rend::vec3 rotation;
		rend::vec3 scale = rend::vec3(1.0f, 1.0f, 1.0f);
		rend::mat4 mat = rend::mat4(1.0f);

	};
}