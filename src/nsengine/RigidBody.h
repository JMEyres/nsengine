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
		/// @param _type Static, Dynamic or Kinematic rigidbody
		void SetType(rp3d::BodyType _type);

		/// @brief Add a collision shape to the rigidbody
		/// @param _shape Collision shape to be added
		void AddCollisionShape(rp3d::CollisionShape* _shape);

		/// @brief Add a trigger collision shape to the rigidbody used when rigidbody doesnt need to collide with other rigidbodies
		/// @param _shape Collision shape to be added
		void AddTriggerCollisionShape(rp3d::CollisionShape* _shape);

		/// @brief Set the bounciness level of the rigidbody
		/// @param _value Bounciness level between 0 and 1, 0 being not bouncy at all, 1 being fully bouncy
		void SetBounciness(float _value);
			
		/// @brief Move the rigidbody with simulated physics forces
		/// @param _x Force to move in x axis
		/// @param _y Force to move in y axis
		/// @param _z Force to move in z axis
		void Move(float _x, float _y, float _z);

		/// @brief Force set the position of the rigidbody and by extension the transform
		/// @param _x Position on x axis
		/// @param _y Position on y axis
		/// @param _z Position on z axis
		void SetPosition(float _x, float _y, float _z);

		/// @brief Get the position of the current rigidbody
		/// @return Vector position of rigidbody in xyz axis
		rend::vec3 GetPos();

		/// @brief Disable rigidbody
		void Disable();

		void Enable();

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
		rp3d::Vector3 originalPosition;
		bool isTrigger = false;
		bool disable = false;
		float bounciness = 0;
	};
}