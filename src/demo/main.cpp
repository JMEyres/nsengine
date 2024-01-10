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
		
		if (getCore()->getInput()->isKeyHeld(KEY_W))
		{
			getEntity()->getComponent<RigidBody>()->move(0, 0, speed * dt);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_A))
		{
			getEntity()->getComponent<RigidBody>()->move(speed * dt, 0, 0);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_S))
		{
			getEntity()->getComponent<RigidBody>()->move(0, 0, -speed * dt);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_D))
		{
			getEntity()->getComponent<RigidBody>()->move(-speed * dt, 0, 0);
		}
		if (getCore()->getInput()->isKeyPressed(KEY_LSHIFT))
		{
			getEntity()->getComponent<AudioSource>()->play();
		}
		if (getCore()->getInput()->isKeyHeld(KEY_H))
		{
			getEntity()->getTransform()->Rotate(-angle * dt, 0, 0);
		}
	}
private:
	float angle = 360.0f;
	float speed = 1.0f;
};

struct CameraController : Component
{
	void onTick()
	{
		float dt = getCore()->getDeltaTime();
		
		// Rotate
		if (getCore()->getInput()->isKeyHeld(KEY_RIGHT))
		{
			getEntity()->getTransform()->Rotate(0, -angle * dt, 0);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_LEFT))
		{
			getEntity()->getTransform()->Rotate(0, angle * dt, 0);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_DOWN))
		{
			getEntity()->getTransform()->Rotate(angle * dt, 0, 0);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_UP))
		{
			getEntity()->getTransform()->Rotate(-angle * dt, 0, 0);
		}

		// Move
		if (getCore()->getInput()->isKeyHeld(KEY_J))
		{
			getEntity()->getTransform()->Move(-speed * dt, 0, 0);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_L))
		{
			getEntity()->getTransform()->Move(speed * dt, 0, 0);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_K))
		{
			getEntity()->getTransform()->Move(0, 0, speed * dt);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_I))
		{
			getEntity()->getTransform()->Move(0, 0, -speed * dt);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_O))
		{
			getEntity()->getTransform()->Move(0, speed * dt, 0);
		}
		if (getCore()->getInput()->isKeyHeld(KEY_U))
		{
			getEntity()->getTransform()->Move(0, -speed * dt, 0);
		}
	}
private:
	float angle = 90.0f;
	float speed = 5.0f;
};

int main()
{
	std::shared_ptr<Core> core = Core::initialize(); // initializes core

	std::shared_ptr<Environment> environment = core->createEnvironment();

	std::shared_ptr<Entity> curuthers = environment->addEntity();
	std::shared_ptr<Entity> triangle = environment->addEntity(); // creating entity, core holds on list
	std::shared_ptr<Entity> floor = environment->addEntity(); 
	std::shared_ptr<Entity> box = environment->addEntity(); 
	std::shared_ptr<Entity> camera = environment->addEntity(); 
	

	camera->addComponent<Camera>();
	camera->addComponent<CameraController>();
	curuthers->addComponent<AudioSource>();
	curuthers->getComponent<AudioSource>()->setAudio(curuthers->getEnvironment()->getCore()->getResources()->load<Audio>("../src/Resources/Audio/dixie_horn.ogg"));

	triangle->addComponent<Player>(); // creating component, entity holds on list
	curuthers->addComponent<Controller>(); 

	triangle->addComponent<TriangleRenderer>(); // creating component, entity holds on list

	curuthers->addComponent<Renderer>();
	floor->addComponent<Renderer>();
	box->addComponent<Renderer>();

	triangle->addComponent<BoxCollider>();

	curuthers->addComponent<BoxCollider>();
	curuthers->getComponent<BoxCollider>()->setSize(2.0f, 2.0f, 2.0f);

	floor->addComponent<BoxCollider>();
	floor->getComponent<BoxCollider>()->setSize(100.0f, 1.0f, 100.0f); 
	
	box->addComponent<BoxCollider>();
	box->getComponent<BoxCollider>()->setSize(1.0f, 1.0f, 1.0f);

	curuthers->addComponent<RigidBody>();
	floor->addComponent<RigidBody>();
	box->addComponent<RigidBody>();

	curuthers->getComponent<Renderer>()->path = "../src/Resources/Models/curuthers.obj";
	floor->getComponent<Renderer>()->path = "../src/Resources/Models/floor.obj";
	box->getComponent<Renderer>()->path = "../src/Resources/Models/Box.obj";
	
	floor->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	box->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	
	triangle->getTransform()->setPosition(rend::vec3(0.0f, 0.0f, -5.0f));
	triangle->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	curuthers->getTransform()->setPosition(rend::vec3(-2.0f, 5.0f, -10.0f));
	curuthers->getTransform()->setRotation(rend::vec3(0.0f, 90.0f, 0.0f));
	curuthers->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	floor->getTransform()->setPosition(rend::vec3(0.0f, -1.0f, 0.0f));
	floor->getTransform()->setScale(rend::vec3(100.0f, 1.0f, 100.0f));

	box->getTransform()->setPosition(rend::vec3(5.0f, 2.0f, -10.0f));
	box->getTransform()->setScale(rend::vec3(5.0f, 5.0f, 5.0f));

	//floor->getComponent<RigidBody>()->
	core->start();

	return 0;
}