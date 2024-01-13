#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "Entity.h"
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

namespace nsengine
{
	struct RigidBody : Component
	{
		void onPhysicsTick();
		void onInitialize();

		void setType(rp3d::BodyType type);
		void addCollisionShape(rp3d::CollisionShape* shape);
			
		void move(float x, float y, float z);
		void rotate(float x, float y, float z);

		rp3d::RigidBody* rb;
	private:
		rp3d::BodyType rbType = rp3d::BodyType::DYNAMIC;
		rp3d::Collider* collider;
		rp3d::CollisionShape* collisionShape;
	};
}