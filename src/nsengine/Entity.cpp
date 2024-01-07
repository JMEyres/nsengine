#include "Entity.h"

namespace nsengine
{
	void Entity::initialize()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			//std::cout << typeid(components.at(ci)->self).name() << std::endl;
			components.at(ci)->initialize();
		}
	}

	void Entity::tick()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			components.at(ci)->tick();
		}
	}

	void Entity::physicsTick()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			components.at(ci)->physicsTick();
		}
	}

	void Entity::display()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			components.at(ci)->display();
		}
	}

	std::shared_ptr<Environment> Entity::getEnvironment()
	{
		return environment.lock();
	}

	std::shared_ptr<Transform> Entity::getTransform()
	{
		return transform.lock();
	}
}