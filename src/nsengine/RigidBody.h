#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "Entity.h"

#include <vector>
#include <reactphysics3d/reactphysics3d.h>

namespace nsengine
{
	/// @brief Component responsible for creating and storing data for a rigidbody, used for collision
	struct RigidBody : Component
	{
		void OnPhysicsTick();
		void OnInitialize();

		/// @brief Set the type for the rigid body
		/// @param type Static, Dynamic or Kinematic rigidbody
		void SetType(rp3d::BodyType type);

		/// @brief Add a collision shape to the rigidbody
		/// @param shape Collision shape to be added
		void AddCollisionShape(rp3d::CollisionShape* shape);

		/// @brief Add a trigger collision shape to the rigidbody used when rigidbody doesnt need to collide with other rigidbodies
		/// @param shape Collision shape to be added
		void AddTriggerCollisionShape(rp3d::CollisionShape* shape);

		/// @brief Set the bounciness level of the rigidbody
		/// @param value Bounciness level between 0 and 1, 0 being not bouncy at all, 1 being fully bouncy
		void SetBounciness(float value);
			
		/// @brief Move the rigidbody with simulated physics forces
		/// @param x Force to move in x axis
		/// @param y Force to move in y axis
		/// @param z Force to move in z axis
		void Move(float x, float y, float z);

		/// @brief Get the position of the current rigidbody
		/// @return Vector position of rigidbody in xyz axis
		rend::vec3 GetPos();

		/// @brief Disable rigidbody
		void Disable();

		/// @brief Get the current rigidbody
		/// @return Pointer to the given rigidbody
		rp3d::RigidBody* GetRigidBody();

	private:
		rp3d::RigidBody* rb;
		rp3d::BodyType rbType = rp3d::BodyType::DYNAMIC;
		rp3d::Collider* collider;
		rp3d::Collider* triggerCollider;
		rp3d::CollisionShape* collisionShape;
		rp3d::CollisionShape* triggerCollisionShape;
		bool isTrigger = false;
		bool disable = false;
		float bounciness = 0;
	};
}