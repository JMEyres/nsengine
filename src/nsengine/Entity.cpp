#include "Entity.h"

namespace nsengine
{
	void Entity::Initialize()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			components.at(ci)->Initialize();
		}
	}

	void Entity::Tick()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			components.at(ci)->Tick();
		}
	}

	void Entity::PhysicsTick()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			components.at(ci)->PhysicsTick();
		}
	}

	void Entity::Display()
	{
		for (size_t ci = 0; ci < components.size(); ++ci)
		{
			components.at(ci)->Display();
		}
	}

	std::shared_ptr<Environment> Entity::GetEnvironment()
	{
		return environment.lock();
	}

	std::shared_ptr<Transform> Entity::GetTransform()
	{
		return transform.lock();
	}
}