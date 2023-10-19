#include <iostream>
#include <nsengine/Core.h>
#include <nsengine/Entity.h>
#include <nsengine/Component.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <rend/Model.h>

using namespace nsengine;

#undef main // SDL2 Wraps everything in its own main so causes a linker error, this stops it looking for that undefines it

int main()
{
	std::shared_ptr<Core> core = Core::initialize(); // initializes core

	std::shared_ptr<Entity> entity = core->addEntity(); // creating entity, core holds on list
	std::shared_ptr<Component> component = entity->addComponent(); // creating component, entity holds on list


	return 0;
}