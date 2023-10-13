#include "Core.h"
#include "Entity.h"



namespace nsengine
{
std::shared_ptr<Core> Core::initialize()
{
	std::shared_ptr<Core> rtn = std::make_shared<Core>(); // make_shared = new

	return rtn;
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	entities.push_back(entity);
	return entity;
}

}