#include "Environment.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"

namespace nsengine
{
	std::shared_ptr<Entity> Environment::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->environment = self; // allows entity to point upwards
		rtn->self = rtn; // will allow component to point upwards

		rtn->addComponent<Transform>();

		entities.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Core> Environment::getCore()
	{
		return core.lock();
	}

	float Environment::getDeltaTime()
	{
		lastTime = SDL_GetTicks();

		float time = SDL_GetTicks();
		float diff = time - lastTime;
		deltaTime = diff / 1000.0f;
		lastTime = time;

		return deltaTime;
	}
}