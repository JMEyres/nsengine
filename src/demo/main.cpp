#include<nsengine/nsengine.h>

using namespace nsengine;

#undef main // SDL2 Wraps everything in its own main so causes a linker error, this stops it looking for that undefines it

struct Player : Component
{
	Player() :
		angle(0) { }
	void onTick()
	{
		float dt = getCore()->getDeltaTime();
		angle += 360.0f*dt;
		getEntity()->getTransform()->setRotation(rend::vec3(0, angle, 0));
	}

private:
	float angle;
};


struct Controller : Component
{
	void onTick()
	{
		float dt = getCore()->getDeltaTime();
		
		if (getCore()->getInput()->isKeyHeld(KEY_L))
		{
			rend::vec3 test = getEntity()->getTransform()->getForward() * 5.0f * dt;
			getEntity()->getTransform()->Move(test);
		}
		//if (getCore()->getInput()->isKeyHeld('d'))
		//{
		//	getEntity()->getTransform()->rotate(angle * dt, 0, 0);
		//}
	}
private:
	float angle = 360.0f;
};

struct CameraController : Component
{
	void onTick()
	{
		float dt = getCore()->getDeltaTime();
		
		// Rotate
		if (getCore()->getInput()->isKeyHeld(KEY_RIGHT))
		{
			rend::vec3 rotation = rend::vec3((0, -angle * dt, 0));
			getEntity()->getTransform()->rotate(rotation);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_LEFT))
		{
			rend::vec3 rotation = rend::vec3((0, angle * dt, 0));
			getEntity()->getTransform()->rotate(rotation);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_DOWN))
		{
			rend::vec3 rotation = rend::vec3((angle * dt, 0, 0));
			getEntity()->getTransform()->rotate(rotation);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_UP))
		{
			rend::vec3 rotation = rend::vec3((-angle * dt, 0, 0));
			getEntity()->getTransform()->rotate(rotation);
		}

		// Move
		if (getCore()->getInput()->isKeyHeld(KEY_A))
		{
			rend::vec3 movement = getEntity()->getTransform()->getLeft() * speed * dt;
			getEntity()->getTransform()->Move(movement);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_D))
		{
			rend::vec3 movement = getEntity()->getTransform()->getRight() * speed * dt;
			getEntity()->getTransform()->Move(movement);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_S))
		{
			rend::vec3 movement = getEntity()->getTransform()->getBack() * speed * dt;
			getEntity()->getTransform()->Move(movement);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_W))
		{
			rend::vec3 movement = getEntity()->getTransform()->getForward() * speed * dt;
			getEntity()->getTransform()->Move(movement);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_SPACE))
		{
			rend::vec3 movement = getEntity()->getTransform()->getUp() * speed * dt;
			getEntity()->getTransform()->Move(movement);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_LCTRL))
		{
			rend::vec3 movement = getEntity()->getTransform()->getDown() * speed * dt;
			getEntity()->getTransform()->Move(movement);
		}
	}
private:
	float angle = 90.0f;
	float speed = 10.0f;
};

int main()
{
	std::shared_ptr<Core> core = Core::initialize(); // initializes core

	std::shared_ptr<Environment> environment = core->createEnvironment();
	std::shared_ptr<Entity> curuthers = environment->addEntity();
	std::shared_ptr<Entity> triangle = environment->addEntity(); // creating entity, core holds on list
	std::shared_ptr<Entity> floor = environment->addEntity(); 
	std::shared_ptr<Entity> camera = environment->addEntity(); 
	

	camera->addComponent<Camera>();
	camera->addComponent<CameraController>();

	triangle->addComponent<Player>(); // creating component, entity holds on list
	curuthers->addComponent<Controller>(); 

	triangle->addComponent<TriangleRenderer>(); // creating component, entity holds on list

	curuthers->addComponent<Renderer>(); // "../src/Resources/Models/curuthers.obj"
	floor->addComponent<Renderer>();

	triangle->addComponent<BoxCollider>();
	curuthers->addComponent<BoxCollider>();
	floor->addComponent<BoxCollider>();

	triangle->addComponent<RigidBody>();
	//curuthers->addComponent<RigidBody>();
	floor->addComponent<RigidBody>();

	curuthers->getComponent<Renderer>()->path = "../src/Resources/Models/curuthers.obj";
	floor->getComponent<Renderer>()->path = "../src/Resources/Models/floor.obj";
	
	triangle->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	floor->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	
	triangle->getTransform()->setPosition(rend::vec3(0.0f, 0.0f, -5.0f));
	triangle->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	curuthers->getTransform()->setPosition(rend::vec3(-2.0f, 5.0f, -10.0f));
	curuthers->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	floor->getTransform()->setPosition(rend::vec3(-2.0f, -1.0f, -10.0f));
	floor->getTransform()->setScale(rend::vec3(100.0f, 1.0f, 100.0f));

	//floor->getComponent<RigidBody>()->
	core->start();

	return 0;
}