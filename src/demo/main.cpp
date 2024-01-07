#include<nsengine/nsengine.h>

using namespace nsengine;

#undef main // SDL2 Wraps everything in its own main so causes a linker error, this stops it looking for that undefines it

struct Player : Component
{
	Player() :
		angle(0) { }
	void onTick()
	{
		float dt = getEntity()->getEnvironment()->getDeltaTime();
		angle += 360.0f*dt;
		getEntity()->getTransform()->setRotation(rend::vec3(0, angle, 0));
	}

private:
	float angle;
};


struct Controller : Component
{
	Controller() :
		angle(0) { }
	void onTick()
	{
		float dt = getEntity()->getEnvironment()->getDeltaTime();
		if (getEntity()->getEnvironment()->getCore()->getInput()->isKeyHeld('a'))
		{
			angle += 5.0f * dt;
			getEntity()->getTransform()->setRotation(glm::vec3(0, -angle, 0));
		}
		if (getEntity()->getEnvironment()->getCore()->getInput()->isKeyPressed('d'))
		{
			//angle += 5.0f * dt;
			getEntity()->getTransform()->setPosition(glm::vec3(0, 0, -5.0f));
		}
	}
private:
	float angle;
};

int main()
{
	std::shared_ptr<Core> core = Core::initialize(); // initializes core

	std::shared_ptr<Environment> environment = core->createEnvironment();
	std::shared_ptr<Entity> curuthers = environment->addEntity();
	std::shared_ptr<Entity> triangle = environment->addEntity(); // creating entity, core holds on list
	std::shared_ptr<Entity> floor = environment->addEntity(); 
	

	triangle->addComponent<Player>(); // creating component, entity holds on list
	curuthers->addComponent<Controller>(); 
	triangle->addComponent<TriangleRenderer>(); // creating component, entity holds on list
	curuthers->addComponent<Renderer>(); // "../src/Resources/Models/curuthers.obj"
	//floor->addComponent<Renderer>();

	triangle->addComponent<BoxCollider>();
	curuthers->addComponent<BoxCollider>();
	floor->addComponent<BoxCollider>();

	triangle->addComponent<RigidBody>();
	curuthers->addComponent<RigidBody>();
	//floor->addComponent<CollisionBody>();

	//curuthers->getComponent<Renderer>()->modelPath = "../src/Resources/Models/curuthers.obj";
	//floor->getComponent<Renderer>()->modelPath = "../src/Resources/Models/floor.obj";

	
	triangle->getTransform()->setPosition(rend::vec3(0.0f, 0.0f, -5.0f));
	triangle->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	curuthers->getTransform()->setPosition(rend::vec3(-2.0f, 0.0f, -10.0f));
	curuthers->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	core->start();

	return 0;
}