#include "Entity.h"
#include "Component.h"
#include "Core.h"

namespace nsengine
{
	void Entity::tick()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			components.at(ci)->tick();
		}
	}

	void Entity::display()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			components.at(ci)->display();
		}
	}

	std::shared_ptr<Core> Entity::getCore()
	{
		return core.lock();
	}
}