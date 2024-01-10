#pragma once
#include "Component.h"
#include <rend/rend.h>
#include <reactphysics3d/reactphysics3d.h>

namespace nsengine
{
	struct CapsuleCollider : Component
	{
		void createCollider(float radius, float height);

		rp3d::CapsuleShape* capsule;
	private:
		float radius;
		float height;
	};
}