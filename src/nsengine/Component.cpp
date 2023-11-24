#include "Component.h"

namespace nsengine
{
	void Component::onInitialize()
	{}
	void Component::onTick()
	{}
	void Component::onDisplay()
	{}

	void Component::initialize()
	{
		onInitialize();
	}
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

