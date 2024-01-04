#pragma once
#include "Component.h"
#include <rend/rend.h>

namespace nsengine
{
	struct BoxCollider : Component
	{
		bool isColliding(glm::vec3 pos, glm::vec3 size);
		glm::vec3 getCollisionResponse(glm::vec3 pos, glm::vec3 size);

	private:
		glm::vec3 size;
		glm::vec3 offset;
	};
}