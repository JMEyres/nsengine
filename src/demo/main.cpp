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
			//getEntity()->getTransform()->Rotate(rend::vec3(0.0f, 10.0f , 0.0f));
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

	std::shared_ptr<Environment> environment = core->createEnvironment();
	std::shared_ptr<Entity> entity = environment->addEntity(); // creating entity, core holds on list
	entity->addComponent<Player>(); // creating component, entity holds on list
	entity->addComponent<TriangleRenderer>(); // creating component, entity holds on list
	//entity->addComponent<Transform>();// creating component, entity holds on list

	core->start();

	return 0;
}