#include<nsengine/nsengine.h>
#include<chrono>

using namespace nsengine;

#undef main // SDL2 Wraps everything in its own main so causes a linker error, this stops it looking for that undefines it

struct Controller : Component
{
	void onTick()
	{
		float dt = getCore()->getDeltaTime();

		glm::vec2 oldMouse;

		glm::vec2 currentMouse = glm::vec2(getCore()->getInput()->mouseX, getCore()->getInput()->mouseY);
		glm::vec2 mouseDelta = oldMouse - currentMouse;

		getEntity()->getTransform()->Rotate(0, mouseDelta.x * 0.1f, 0);

		oldMouse = currentMouse;
		glm::vec3 otherPos = box->getTransform()->getPosition();
		glm::vec3 otherSize = box->getComponent<BoxCollider>()->getSize();
		if (getEntity()->getComponent<BoxCollider>()->isColliding(otherPos, otherSize))
			std::cout << "HIT" << std::endl;
		// ^^^ do same check for pickup, if collision true do pickup logic
		// then destroy
		// for anim do sprite animation

		if (getCore()->getInput()->isKeyHeld(KEY_W))
			getEntity()->getComponent<RigidBody>()->move(0, 0, speed * dt);
		if (getCore()->getInput()->isKeyHeld(KEY_A))
			getEntity()->getComponent<RigidBody>()->move(speed * dt, 0, 0);
		if (getCore()->getInput()->isKeyHeld(KEY_S))
			getEntity()->getComponent<RigidBody>()->move(0, 0, -speed * dt);
		if (getCore()->getInput()->isKeyHeld(KEY_D))
			getEntity()->getComponent<RigidBody>()->move(-speed * dt, 0, 0);
		if (getCore()->getInput()->isKeyReleased(KEY_SPACE))
		{
			getEntity()->getComponent<RigidBody>()->move(0, 500, 0);
			getEntity()->getComponent<AudioSource>()->play();
		}
		if (getCore()->getInput()->isKeyPressed(KEY_ESCAPE))
			getCore()->stop();
		
	}
	std::shared_ptr<Entity> box;
private:
	float angle = 360.0f;
	float speed = 1000.0f;
};

struct CameraController : Component
{
	void onTick()
	{
		float dt = getCore()->getDeltaTime();
		
		if (getCore()->getInput()->isKeyHeld(KEY_TAB))
			follow = !follow;

		if(follow)
			getEntity()->getComponent<Camera>()->Follow();
		else
		{
			if (getCore()->getInput()->isKeyHeld(KEY_RIGHT))
				getEntity()->getTransform()->Rotate(0, -angle * dt, 0);
			if (getCore()->getInput()->isKeyHeld(KEY_LEFT))
				getEntity()->getTransform()->Rotate(0, angle * dt, 0);
			if (getCore()->getInput()->isKeyHeld(KEY_DOWN))
				getEntity()->getTransform()->Rotate(angle * dt, 0, 0);
			if (getCore()->getInput()->isKeyHeld(KEY_UP))
				getEntity()->getTransform()->Rotate(-angle * dt, 0, 0);

			// Move
			if (getCore()->getInput()->isKeyHeld(KEY_J))
				getEntity()->getTransform()->Move(-speed * dt, 0, 0);
			if (getCore()->getInput()->isKeyHeld(KEY_L))
				getEntity()->getTransform()->Move(speed * dt, 0, 0);
			if (getCore()->getInput()->isKeyHeld(KEY_K))
				getEntity()->getTransform()->Move(0, 0, speed * dt);
			if (getCore()->getInput()->isKeyHeld(KEY_I))
				getEntity()->getTransform()->Move(0, 0, -speed * dt);
			if (getCore()->getInput()->isKeyHeld(KEY_O))
				getEntity()->getTransform()->Move(0, speed * dt, 0);
			if (getCore()->getInput()->isKeyHeld(KEY_U))
				getEntity()->getTransform()->Move(0, -speed * dt, 0);
		}
	}
private:
	
	bool follow = true;
	float angle = 90.0f;
	float speed = 5.0f;
};

int main()
{
	std::shared_ptr<Core> core = Core::initialize(); // initializes core

	std::shared_ptr<Environment> environment = core->createEnvironment();

	std::shared_ptr<Entity> curuthers = environment->addEntity();
	std::shared_ptr<Entity> quad = environment->addEntity(); // creating entity, core holds on list
	std::shared_ptr<Entity> floor = environment->addEntity(); 
	std::shared_ptr<Entity> box = environment->addEntity(); 
	std::shared_ptr<Entity> box2 = environment->addEntity(); 
	std::shared_ptr<Entity> box3 = environment->addEntity(); 
	std::shared_ptr<Entity> box4 = environment->addEntity(); 
	std::shared_ptr<Entity> box5 = environment->addEntity(); 
	std::shared_ptr<Entity> camera = environment->addEntity(); 
	std::shared_ptr<Entity> pickup = environment->addEntity(); 
	
	camera->addComponent<Camera>();
	camera->addComponent<Gui>();
	camera->getComponent<Camera>()->SetTarget(curuthers);
	camera->getComponent<Camera>()->SetOffset(1.0f, 4.5f, 0.0f);
	camera->addComponent<CameraController>();

	camera->getComponent<Gui>()->setPath("/Fonts/console.png");
	camera->getComponent<Gui>()->enableAsTimer(true);

	curuthers->addComponent<AudioSource>();
	curuthers->getComponent<AudioSource>()->setAudio(curuthers->getEnvironment()->getCore()->getResources()->load<Audio>("/Audio/jump.ogg"));

	curuthers->addComponent<Controller>();

	quad->addComponent<SpriteRenderer>(); // creating component, entity holds on list

	std::vector<std::shared_ptr<Texture>> spriteAnim;
	spriteAnim.push_back(quad->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_1.png"));
	spriteAnim.push_back(quad->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_2.png"));
	spriteAnim.push_back(quad->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_3.png"));
	spriteAnim.push_back(quad->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_4.png"));
	spriteAnim.push_back(quad->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_5.png"));
	spriteAnim.push_back(quad->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_6.png"));
	spriteAnim.push_back(quad->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_7.png"));
	spriteAnim.push_back(quad->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_9.png"));
	spriteAnim.push_back(quad->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_8.png"));
	
	quad->getComponent<SpriteRenderer>()->Animate(spriteAnim);

	curuthers->addComponent<Renderer>();
	floor->addComponent<Renderer>();

	box->addComponent<Renderer>();
	box2->addComponent<Renderer>();
	box3->addComponent<Renderer>();
	box4->addComponent<Renderer>();
	box5->addComponent<Renderer>();

	curuthers->addComponent<CapsuleCollider>();
	curuthers->getComponent<CapsuleCollider>()->createCollider(1.0f, 1.0f);
	curuthers->addComponent<BoxCollider>();
	curuthers->getComponent<BoxCollider>()->createCollider(10.0f, 10.0f, 10.0f);

	floor->addComponent<BoxCollider>();
	floor->getComponent<BoxCollider>()->createCollider(50.0f, 1.0f, 50.0f);
	
	box->addComponent<BoxCollider>();
	box->getComponent<BoxCollider>()->createCollider(5.0f, 11.0f, 5.0f);

	box2->addComponent<BoxCollider>();
	box2->getComponent<BoxCollider>()->createCollider(5.0f, 11.0f, 5.0f);

	box3->addComponent<BoxCollider>();
	box3->getComponent<BoxCollider>()->createCollider(5.0f, 11.0f, 5.0f);

	box4->addComponent<BoxCollider>();
	box4->getComponent<BoxCollider>()->createCollider(5.0f, 11.0f, 5.0f);

	box5->addComponent<BoxCollider>();
	box5->getComponent<BoxCollider>()->createCollider(5.0f, 11.0f, 5.0f);

	curuthers->addComponent<RigidBody>();
	floor->addComponent<RigidBody>();
	floor->getComponent<RigidBody>()->setBounciness(1);
	box->addComponent<RigidBody>();
	box2->addComponent<RigidBody>();
	box3->addComponent<RigidBody>();
	box4->addComponent<RigidBody>();
	box5->addComponent<RigidBody>();

	curuthers->getComponent<Renderer>()->path = "/Models/curuthers.obj";
	floor->getComponent<Renderer>()->path = "/Models/floor.obj";
	box->getComponent<Renderer>()->path = "/Models/Cube.obj";
	box2->getComponent<Renderer>()->path = "/Models/Cube.obj";
	box3->getComponent<Renderer>()->path = "/Models/Cube.obj";
	box4->getComponent<Renderer>()->path = "/Models/Cube.obj";
	box5->getComponent<Renderer>()->path = "/Models/Cube.obj";
	
	curuthers->getComponent<RigidBody>()->addCollisionShape(curuthers->getComponent<CapsuleCollider>()->capsule);
	curuthers->getComponent<RigidBody>()->addTriggerCollisionShape(curuthers->getComponent<BoxCollider>()->box);
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
	
	quad->getTransform()->setPosition(rend::vec3(0,35,-50));
	quad->getTransform()->setScale(rend::vec3(50));

	curuthers->getTransform()->setPosition(rend::vec3(0.0f, 5.0f, 0.0f));
	curuthers->getTransform()->setRotation(rend::vec3(0.0f, 90.0f, 0.0f));
	curuthers->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	floor->getTransform()->setPosition(rend::vec3(0.0f, -1.0f, 0.0f));
	floor->getTransform()->setScale(rend::vec3(100.0f, 1.0f, 100.0f));

	box->getTransform()->setPosition(rend::vec3(-5.0f, 10.0f, 0.0f));
	box->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box2->getTransform()->setPosition(rend::vec3(15.0f, 4.0f, 0.0f));
	box2->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box3->getTransform()->setPosition(rend::vec3(25.0f, 6.0f, 0.0f));
	box3->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box4->getTransform()->setPosition(rend::vec3(35.0f, 8.0f, 0.0f));
	box4->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box5->getTransform()->setPosition(rend::vec3(45.0f, 10.0f, 0.0f));
	box5->getTransform()->setScale(rend::vec3(10.0f, 10.0f, 10.0f));

	curuthers->getComponent<Controller>()->box = box;

	core->start();

	return 0;
}