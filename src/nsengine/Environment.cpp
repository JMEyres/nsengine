#include "Environment.h"

namespace nsengine
{
	std::shared_ptr<Entity> Environment::AddEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		rtn->environment = self; // allows entity to point upwards
		rtn->self = rtn; // will allow component to point upwards

		rtn->transform = rtn->AddComponent<Transform>(); // add transform component and set transform pointer

		entities.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Core> Environment::GetCore()
	{
		return core.lock();
	}

	void Environment::AddCamera(std::shared_ptr<Camera> cam)
	{
		cameras.push_back(cam);
	}

	std::shared_ptr<Camera> Environment::GetCamera(int camIndex)
	{
		return cameras[camIndex];
	}
}