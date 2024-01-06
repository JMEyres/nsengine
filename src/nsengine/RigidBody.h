#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "Entity.h"
#include "pellet/btBulletDynamicsCommon.h"
#include <vector>

namespace nsengine
{
	struct RigidBody : Component
	{
		float mass = 0.f;
		btVector3 localInertia = btVector3(0,0,0);
		
		void onTick();
		void onInitialize();
	};
}