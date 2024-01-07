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
		void onTick();
		void onPhysicsTick();
		void onInitialize();

	private:
		rp3d::RigidBody* rb;
		rp3d::Collider* collider;
	};
}