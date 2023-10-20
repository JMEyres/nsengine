#include<nsengine/nsengine.h>

using namespace nsengine;

#undef main // SDL2 Wraps everything in its own main so causes a linker error, this stops it looking for that undefines it

struct Player : Component
{
	Player() :
		count(0) { }
	void onTick()
	{
		++count;
		//std::cout << "Ticking..." << std::endl;

		if (count > 10)
		{
			//getEntity()->getCore()->stop();
#			
			// Potential shortcuts for later	
			//getEntity()->kill(); 
			//getCore()->stop();
		}
	}

private:
	int count;
};

int main()
{
	std::shared_ptr<Core> core = Core::initialize(); // initializes core

	std::shared_ptr<Entity> entity = core->addEntity(); // creating entity, core holds on list
	std::shared_ptr<Component> component = entity->addComponent<Player>(); // creating component, entity holds on list

	core->start();

	return 0;
}