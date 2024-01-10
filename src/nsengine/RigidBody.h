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
		
		void move(float x, float y, float z);
		void rotate(float x, float y, float z);

	private:
		rp3d::BodyType rbType = rp3d::BodyType::DYNAMIC;
		rp3d::RigidBody* rb;
		rp3d::Collider* collider;
	};
}