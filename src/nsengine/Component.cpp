#include "Component.h"
#include "Entity.h"

namespace nsengine
{
	void Component::onTick()
	{}
	void Component::onDisplay()
	{}

	void Component::tick()
	{
		onTick();
	}
	void Component::display()
	{
		onDisplay();
	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock();
	}
}

