#pragma once
#include "Component.h"
#include <rend/rend.h>
#include <reactphysics3d/reactphysics3d.h>

namespace nsengine
{
	struct BoxCollider : Component
	{
		bool isColliding(glm::vec3 otherPos, glm::vec3 otherSize);
		void createCollider(float x, float y, float z);
		rend::vec3 getSize();

		rp3d::BoxShape* box;
	private:
		rp3d::Vector3 size = rp3d::Vector3(1,1,1);
	};
}