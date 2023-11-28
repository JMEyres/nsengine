#pragma once
#include<memory>
#include<vector>
#include <iostream>

#include "Entity.h"
#include "Transform.h"

namespace nsengine
{
	struct Entity; // just says it exists - not defined yet
	struct Core;
	struct Environment
	{
		float getDeltaTime();
		std::shared_ptr<Entity> addEntity(); // constructs addEntity function
		std::shared_ptr<Core> getCore();

	private:
		friend struct Core;

		std::weak_ptr<Core> core; // core owns environments
		std::weak_ptr<Environment> self;


		std::vector<std::shared_ptr<Entity> > entities; // List of entities

		float lastTime = SDL_GetTicks();
		float deltaTime;
	};
}