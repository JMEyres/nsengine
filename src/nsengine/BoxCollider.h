#pragma once
#include "Component.h"
#include <rend/rend.h>
#include <pellet/btBulletDynamicsCommon.h>

namespace nsengine
{
	struct BoxCollider : Component
	{
		bool isColliding(glm::vec3 pos, glm::vec3 size);
		glm::vec3 getCollisionResponse(glm::vec3 pos, glm::vec3 size);

		void onInitialize();

		btCollisionShape* collider;
		glm::vec3 size;
		glm::vec3 offset;
	};
}