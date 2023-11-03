#pragma once
#include<memory>
#include<vector>

namespace nsengine
{
	struct Entity; // just says it exists - not defined yet
	struct Environment
	{
		float getDeltaTime();
		std::shared_ptr<Entity> addEntity(); // constructs addEntity function

	private:
		friend struct Core;

		std::weak_ptr<Core> core; // core owns environments
		std::weak_ptr<Environment> self;

		std::shared_ptr<Core> getCore();

		std::vector<std::shared_ptr<Entity> > entities; // List of entities

		float lastTime;
		float deltaTime;
	};
}