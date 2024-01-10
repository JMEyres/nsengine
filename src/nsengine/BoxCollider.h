#pragma once
#include "Component.h"
#include <rend/rend.h>
#include <reactphysics3d/reactphysics3d.h>

namespace nsengine
{
	struct BoxCollider : Component
	{
		bool isColliding(glm::vec3 pos, glm::vec3 size);
		glm::vec3 getCollisionResponse(glm::vec3 pos, glm::vec3 size);

		void onInitialize();
		void setSize(float x, float y, float z);
		rp3d::BoxShape* box;
	private:
		glm::vec3 size = glm::vec3(1);
		glm::vec3 offset;
	};
}