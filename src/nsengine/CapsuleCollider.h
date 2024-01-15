#pragma once
#include "Component.h"
#include <rend/rend.h>
#include <reactphysics3d/reactphysics3d.h>

namespace nsengine
{
	struct CapsuleCollider : Component
	{
		/// @brief Create a capsule collider
		/// @param radius Radius of capsule
		/// @param height Height of capsule
		void CreateCollider(float radius, float height);

		/// @brief Gets the collision shape of the box collider
		/// @return Collision shape as Capsule shape from React Physics 3D
		rp3d::CapsuleShape* GetCollisionShape();
	private:
		rp3d::CapsuleShape* capsule;
		float radius;
		float height;
	};
}