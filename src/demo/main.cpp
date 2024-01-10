#include<nsengine/nsengine.h>
#include<filesystem>

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
		if (getCore()->getInput()->isKeyReleased(KEY_SPACE))
		{
			getEntity()->getComponent<RigidBody>()->move(0, 500, 0);
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
	float speed = 1000.0f;
};

struct CameraController : Component
{
	void onTick()
	{
		getEntity()->getComponent<Camera>()->Follow();
	}
};


struct DebugCameraController : Component
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
	std::shared_ptr<Entity> box2 = environment->addEntity(); 
	std::shared_ptr<Entity> box3 = environment->addEntity(); 
	std::shared_ptr<Entity> box4 = environment->addEntity(); 
	std::shared_ptr<Entity> box5 = environment->addEntity(); 
	std::shared_ptr<Entity> camera = environment->addEntity(); 
	
	camera->addComponent<Camera>();
	camera->getComponent<Camera>()->SetTarget(curuthers);
	camera->getComponent<Camera>()->SetOffset(-15,5,0);
	camera->addComponent<CameraController>();
	camera->addComponent<DebugCameraController>();

	curuthers->addComponent<AudioSource>();
	curuthers->getComponent<AudioSource>()->setAudio(curuthers->getEnvironment()->getCore()->getResources()->load<Audio>("/Audio/dixie_horn.ogg"));

	triangle->addComponent<Player>(); // creating component, entity holds on list
	curuthers->addComponent<Controller>(); 

	//triangle->addComponent<TriangleRenderer>(); // creating component, entity holds on list

	curuthers->addComponent<Renderer>();
	floor->addComponent<Renderer>();

	box->addComponent<Renderer>();
	box2->addComponent<Renderer>();
	box3->addComponent<Renderer>();
	box4->addComponent<Renderer>();
	box5->addComponent<Renderer>();

	triangle->addComponent<BoxCollider>();

	curuthers->addComponent<CapsuleCollider>();
	curuthers->getComponent<CapsuleCollider>()->createCollider(1.0f, 2.0f);

	floor->addComponent<BoxCollider>();
	floor->getComponent<BoxCollider>()->createCollider(100.0f, 1.0f, 100.0f);
	
	box->addComponent<BoxCollider>();
	box->getComponent<BoxCollider>()->createCollider(4.0f, 5.0f, 4.0f);

	box2->addComponent<BoxCollider>();
	box2->getComponent<BoxCollider>()->createCollider(4.0f, 5.0f, 4.0f);

	box3->addComponent<BoxCollider>();
	box3->getComponent<BoxCollider>()->createCollider(4.0f, 5.0f, 4.0f);

	box4->addComponent<BoxCollider>();
	box4->getComponent<BoxCollider>()->createCollider(4.0f, 5.0f, 4.0f);

	box5->addComponent<BoxCollider>();
	box5->getComponent<BoxCollider>()->createCollider(4.0f, 5.0f, 4.0f);

	curuthers->addComponent<RigidBody>();
	floor->addComponent<RigidBody>();
	box->addComponent<RigidBody>();
	box2->addComponent<RigidBody>();
	box3->addComponent<RigidBody>();
	box4->addComponent<RigidBody>();
	box5->addComponent<RigidBody>();

	curuthers->getComponent<Renderer>()->path = "/Models/curuthers.obj";
	floor->getComponent<Renderer>()->path = "/Models/floor.obj";
	box->getComponent<Renderer>()->path = "/Models/Box.obj";
	box2->getComponent<Renderer>()->path = "/Models/Box.obj";
	box3->getComponent<Renderer>()->path = "/Models/Box.obj";
	box4->getComponent<Renderer>()->path = "/Models/Box.obj";
	box5->getComponent<Renderer>()->path = "/Models/Box.obj";
	
	curuthers->getComponent<RigidBody>()->addCollisionShape(curuthers->getComponent<CapsuleCollider>()->capsule);
	floor->getComponent<RigidBody>()->addCollisionShape(floor->getComponent<BoxCollider>()->box);
	box->getComponent<RigidBody>()->addCollisionShape(box->getComponent<BoxCollider>()->box);
	box2->getComponent<RigidBody>()->addCollisionShape(box2->getComponent<BoxCollider>()->box);
	box3->getComponent<RigidBody>()->addCollisionShape(box3->getComponent<BoxCollider>()->box);
	box4->getComponent<RigidBody>()->addCollisionShape(box4->getComponent<BoxCollider>()->box);
	box5->getComponent<RigidBody>()->addCollisionShape(box5->getComponent<BoxCollider>()->box);

	floor->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	box->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	box2->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	box3->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	box4->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	box5->getComponent<RigidBody>()->setType(rp3d::BodyType::STATIC);
	
	triangle->getTransform()->setPosition(rend::vec3(0.0f, 0.0f, -5.0f));
	triangle->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	curuthers->getTransform()->setPosition(rend::vec3(0.0f, 5.0f, 0.0f));
	curuthers->getTransform()->setRotation(rend::vec3(0.0f, 90.0f, 0.0f));
	curuthers->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	floor->getTransform()->setPosition(rend::vec3(0.0f, -1.0f, 0.0f));
	floor->getTransform()->setScale(rend::vec3(100.0f, 1.0f, 100.0f));

	box->getTransform()->setPosition(rend::vec3(5.0f, 2.0f, 0.0f));
	box->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box2->getTransform()->setPosition(rend::vec3(15.0f, 4.0f, 0.0f));
	box2->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box3->getTransform()->setPosition(rend::vec3(25.0f, 6.0f, 0.0f));
	box3->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box4->getTransform()->setPosition(rend::vec3(35.0f, 8.0f, 0.0f));
	box4->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box5->getTransform()->setPosition(rend::vec3(45.0f, 10.0f, 0.0f));
	box5->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	//floor->getComponent<RigidBody>()->
	//std::cout << curuthers->getComponent<BoxCollider>()->box->to_string() << std::endl;

	core->start();

	return 0;
}