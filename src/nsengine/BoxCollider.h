#pragma once
#include "Component.h"
#include <rend/rend.h>
#include <reactphysics3d/reactphysics3d.h>

namespace nsengine
{
	struct BoxCollider : Component
	{
		void createCollider(float x, float y, float z);

		rp3d::BoxShape* box;
	private:
		rp3d::Vector3 size = rp3d::Vector3(1,1,1);
	};
}