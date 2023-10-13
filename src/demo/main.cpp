#include <iostream>
#include <nsengine/Core.h>
#include <nsengine/Entity.h>
#include <nsengine/Component.h>

using namespace nsengine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize(); // initializes core

	std::shared_ptr<Entity> entity = core->addEntity(); // creating entity, core holds on list
	std::shared_ptr<Component> component = entity->addComponent(); // creating component, entity holds on list

	return 0;
}