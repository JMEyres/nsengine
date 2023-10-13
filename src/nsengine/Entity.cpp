#include "Entity.h"
#include "Component.h"

namespace nsengine
{
	std::shared_ptr<Component> Entity::addComponent()
	{
		std::shared_ptr<Component> component = std::make_shared<Component>();
		components.push_back(component);

		return component;
	}
}