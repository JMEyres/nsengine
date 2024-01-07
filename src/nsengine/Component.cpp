#include "Component.h"

namespace nsengine
{
	void Component::onInitialize()
	{}
	void Component::onTick()
	{}
	void Component::onPhysicsTick()
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
	void Component::physicsTick()
	{
		onPhysicsTick();
	}
	void Component::display()
	{
		onDisplay();
	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock();
	}

	std::shared_ptr<Core> Component::getCore()
	{
		return core.lock();
	}
}

