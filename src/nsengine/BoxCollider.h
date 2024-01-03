#pragma once
#include "Component.h"
#include <rend/rend.h>

namespace nsengine
{
	struct BoxCollider : Component
	{
		bool Colliding(BoxCollider& other);

	private:
		glm::vec3 size;
		glm::vec3 offset;
	};
}