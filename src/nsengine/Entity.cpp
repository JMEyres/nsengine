#include "Entity.h"
#include "Component.h"

namespace nsengine
{
	std::shared_ptr<Component> Entity::addComponent()
	{
		std::shared_ptr<Component> rtn = std::make_shared<Component>();

		return rtn;
	}
}