#pragma once
#include "Component.h"
#include <rend/rend.h>
#include <reactphysics3d/reactphysics3d.h>

namespace nsengine
{
	/// @brief Box collider component used for collision
	struct BoxCollider : Component
	{
		/// @brief Simple AABB collision between two objects
		/// @param otherPos Position of other object
		/// @param otherSize Size of other object
		/// @return True/false depending on collision
		bool IsColliding(glm::vec3 otherPos, glm::vec3 otherSize);

		/// @brief Create box collider for use in rigidbody and collision detection
		/// @param x Half extent in x axis
		/// @param y Half extent in y axis
		/// @param z Half extent in z axis
		void CreateCollider(float x, float y, float z);

		/// @brief Gets the size of the box collider
		/// @return Size in a vector 3
		rend::vec3 GetSize();

		/// @brief Gets the collision shape of the box collider
		/// @return Collision shape as Box shape from React Physics 3D
		rp3d::BoxShape* GetCollisionShape();

	private:
		rp3d::BoxShape* box;
		rp3d::Vector3 size = rp3d::Vector3(1,1,1);
	};
}