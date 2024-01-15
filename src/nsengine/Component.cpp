#include "Component.h"

namespace nsengine
{
	void Component::OnInitialize()
	{}
	void Component::OnTick()
	{}
	void Component::OnPhysicsTick()
	{}
	void Component::OnCreate()
	{}
	void Component::OnDisplay()
	{}

	void Component::Initialize()
	{
		OnInitialize();
	}
	void Component::Tick()
	{
		OnTick();
	}
	void Component::PhysicsTick()
	{
		OnPhysicsTick();
	}
	void Component::Create()
	{
		OnCreate();
	}
	void Component::Display()
	{
		OnDisplay();
	}

	std::shared_ptr<Entity> Component::GetEntity()
	{
		return entity.lock();
	}

	std::shared_ptr<Core> Component::GetCore()
	{
		return core.lock();
	}
}

