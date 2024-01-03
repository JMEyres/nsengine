#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "Entity.h"
#include <vector>

namespace nsengine
{
	struct RigidBody : Component
	{
		void onTick();
	};
}