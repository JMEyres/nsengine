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
	struct Camera;
	struct Environment
	{
		std::shared_ptr<Entity> addEntity(); // constructs addEntity function
		void addCamera(std::shared_ptr<Camera> cam);

		std::shared_ptr<Core> getCore();
		std::shared_ptr<Camera> getCamera(int camIndex);

	private:
		friend struct Core;

		std::weak_ptr<Core> core; // core owns environments
		std::weak_ptr<Environment> self;

		std::vector<std::shared_ptr<Entity> > entities; // List of entities
		std::vector<std::shared_ptr<Camera> > cameras; // List of entities
	};
}