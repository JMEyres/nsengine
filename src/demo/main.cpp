#include<nsengine/nsengine.h>
#include<chrono>
#include<filesystem>

using namespace nsengine;

#undef main // SDL2 Wraps everything in its own main so causes a linker error, this stops it looking for that undefines it

struct Controller : Component
{
	void OnTick()
	{
		std::shared_ptr<Camera> cam = GetEntity()->GetEnvironment()->GetCamera(0);
		float dt = GetCore()->GetDeltaTime();

		glm::vec2 oldMouse;

		glm::vec2 currentMouse = glm::vec2(GetCore()->GetInput()->GetMouseX(), GetCore()->GetInput()->GetMouseY());
		glm::vec2 mouseDelta = oldMouse - currentMouse;

		GetEntity()->GetTransform()->Rotate(0, mouseDelta.x * 0.1f, 0);

		oldMouse = currentMouse;

		glm::vec3 finishPos = finish->GetTransform()->GetPosition();
		glm::vec3 finishSize = finish->GetComponent<BoxCollider>()->GetSize();
		if (GetEntity()->GetComponent<BoxCollider>()->IsColliding(finishPos, finishSize) && !finished)
		{
			finished = true;
			std::cout << "Finish" << std::endl;
			finish->GetComponent<AudioSource>()->Play();
		}

		if (pickup)
		{
			glm::vec3 otherPos = pickup->GetTransform()->GetPosition();
			glm::vec3 otherSize = pickup->GetComponent<BoxCollider>()->GetSize();
			if (GetEntity()->GetComponent<BoxCollider>()->IsColliding(otherPos, otherSize))
			{
				pickup->GetComponent<RigidBody>()->Disable();
				cam->GetEntity()->GetComponent<Gui>()->SetTimer(cam->GetEntity()->GetComponent<Gui>()->GetTimer()-5);
			}
		}

		if (GetCore()->GetInput()->IsKeyHeld(KEY_W))
			GetEntity()->GetComponent<RigidBody>()->Move(0, 0, speed * dt);
		if (GetCore()->GetInput()->IsKeyHeld(KEY_A))
			GetEntity()->GetComponent<RigidBody>()->Move(speed * dt, 0, 0);
		if (GetCore()->GetInput()->IsKeyHeld(KEY_S))
			GetEntity()->GetComponent<RigidBody>()->Move(0, 0, -speed * dt);
		if (GetCore()->GetInput()->IsKeyHeld(KEY_D))
			GetEntity()->GetComponent<RigidBody>()->Move(-speed * dt, 0, 0);
		if (GetCore()->GetInput()->IsKeyReleased(KEY_SPACE))
		{
			GetEntity()->GetComponent<RigidBody>()->Move(0, 500, 0);
			GetEntity()->GetComponent<AudioSource>()->Play();
		}
		if (GetCore()->GetInput()->IsKeyPressed(KEY_ESCAPE))
			GetCore()->Stop();
	}

	std::shared_ptr<Entity> finish;
	std::shared_ptr<Entity> pickup;
private:
	float angle = 360.0f;
	float speed = 1000.0f;
	bool finished = false;
};

struct CameraController : Component
{
	void OnTick()
	{
		float dt = GetCore()->GetDeltaTime();
		
		if (GetCore()->GetInput()->IsKeyHeld(KEY_TAB))
			follow = !follow;

		if(follow)
			GetEntity()->GetComponent<Camera>()->Follow();
		else
		{
			if (GetCore()->GetInput()->IsKeyHeld(KEY_RIGHT))
				GetEntity()->GetTransform()->Rotate(0, -angle * dt, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_LEFT))
				GetEntity()->GetTransform()->Rotate(0, angle * dt, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_DOWN))
				GetEntity()->GetTransform()->Rotate(angle * dt, 0, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_UP))
				GetEntity()->GetTransform()->Rotate(-angle * dt, 0, 0);

			// Move
			if (GetCore()->GetInput()->IsKeyHeld(KEY_J))
				GetEntity()->GetTransform()->Move(-speed * dt, 0, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_L))
				GetEntity()->GetTransform()->Move(speed * dt, 0, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_K))
				GetEntity()->GetTransform()->Move(0, 0, speed * dt);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_I))
				GetEntity()->GetTransform()->Move(0, 0, -speed * dt);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_O))
				GetEntity()->GetTransform()->Move(0, speed * dt, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_U))
				GetEntity()->GetTransform()->Move(0, -speed * dt, 0);
		}
	}
private:
	
	bool follow = true;
	float angle = 90.0f;
	float speed = 5.0f;
};

int main()
{
	std::shared_ptr<Core> core = Core::Initialize(); // initializes core

	std::shared_ptr<Environment> environment = core->CreateEnvironment();

	std::shared_ptr<Entity> curuthers = environment->AddEntity();
	std::shared_ptr<Entity> quad = environment->AddEntity(); // creating entity, core holds on list
	std::shared_ptr<Entity> floor = environment->AddEntity(); 
	std::shared_ptr<Entity> box = environment->AddEntity(); 
	std::shared_ptr<Entity> box2 = environment->AddEntity(); 
	std::shared_ptr<Entity> box3 = environment->AddEntity(); 
	std::shared_ptr<Entity> box4 = environment->AddEntity(); 
	std::shared_ptr<Entity> box5 = environment->AddEntity(); 
	std::shared_ptr<Entity> camera = environment->AddEntity(); 
	std::shared_ptr<Entity> pickup = environment->AddEntity(); 
	std::shared_ptr<Entity> finish = environment->AddEntity(); 
	
	camera->AddComponent<Camera>();
	camera->AddComponent<Gui>();
	camera->AddComponent<CameraController>();

	camera->GetComponent<Camera>()->SetTarget(curuthers);
	camera->GetComponent<Camera>()->SetOffset(1.0f, 4.5f, 0.0f);

	camera->GetComponent<Gui>()->SetPath("/Fonts/console.png");
	camera->GetComponent<Gui>()->EnableAsTimer(true);

	curuthers->AddComponent<AudioSource>();
	curuthers->GetComponent<AudioSource>()->SetAudio(curuthers->GetEnvironment()->GetCore()->GetResources()->Load<Audio>("/Audio/jump.ogg"));

	finish->AddComponent<AudioSource>();
	finish->GetComponent<AudioSource>()->SetAudio(curuthers->GetEnvironment()->GetCore()->GetResources()->Load<Audio>("/Audio/dixie_horn.ogg"));

	curuthers->AddComponent<Controller>();

	quad->AddComponent<SpriteRenderer>(); // creating component, entity holds on list
	pickup->AddComponent<SpriteRenderer>();

	std::vector<std::shared_ptr<Texture>> spriteAnim;
	spriteAnim = quad->GetEnvironment()->GetCore()->GetResources()->LoadAnimation("/Textures/SpriteAnim", 9);
	quad->GetComponent<SpriteRenderer>()->Animate(spriteAnim);

	std::vector<std::shared_ptr<Texture>> clockAnim;
	clockAnim = pickup->GetEnvironment()->GetCore()->GetResources()->LoadAnimation("/Textures/Clock", 27);
	pickup->GetComponent<SpriteRenderer>()->Animate(clockAnim);

	curuthers->AddComponent<Renderer>();
	floor->AddComponent<Renderer>();

	box->AddComponent<Renderer>();
	box2->AddComponent<Renderer>();
	box3->AddComponent<Renderer>();
	box4->AddComponent<Renderer>();
	box5->AddComponent<Renderer>();

	curuthers->AddComponent<CapsuleCollider>();
	curuthers->GetComponent<CapsuleCollider>()->CreateCollider(1.0f, 1.0f);

	curuthers->AddComponent<BoxCollider>();
	curuthers->GetComponent<BoxCollider>()->CreateCollider(10.0f, 10.0f, 10.0f);

	pickup->AddComponent<BoxCollider>();
	pickup->GetComponent<BoxCollider>()->CreateCollider(1.0f, 1.0f, 1.0f);

	floor->AddComponent<BoxCollider>();
	floor->GetComponent<BoxCollider>()->CreateCollider(50.0f, 1.0f, 50.0f);
	
	box->AddComponent<BoxCollider>();
	box->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);

	box2->AddComponent<BoxCollider>();
	box2->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);

	box3->AddComponent<BoxCollider>();
	box3->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);

	box4->AddComponent<BoxCollider>();
	box4->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);

	box5->AddComponent<BoxCollider>();
	box5->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);

	finish->AddComponent<BoxCollider>();
	finish->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);

	curuthers->AddComponent<RigidBody>();
	floor->AddComponent<RigidBody>();
	pickup->AddComponent<RigidBody>();
	box->AddComponent<RigidBody>();
	box2->AddComponent<RigidBody>();
	box3->AddComponent<RigidBody>();
	box4->AddComponent<RigidBody>();
	box5->AddComponent<RigidBody>();
	finish->AddComponent<RigidBody>();

	floor->GetComponent<RigidBody>()->SetBounciness(0.5f);

	curuthers->GetComponent<Renderer>()->SetPath("/Models/curuthers.obj");
	floor->GetComponent<Renderer>()->SetPath("/Models/floor.obj");
	box->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");
	box2->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");
	box3->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");
	box4->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");
	box5->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");
	
	curuthers->GetComponent<RigidBody>()->AddCollisionShape(curuthers->GetComponent<CapsuleCollider>()->GetCollisionShape());
	floor->GetComponent<RigidBody>()->AddCollisionShape(floor->GetComponent<BoxCollider>()->GetCollisionShape());
	pickup->GetComponent<RigidBody>()->AddCollisionShape(pickup->GetComponent<BoxCollider>()->GetCollisionShape());
	box->GetComponent<RigidBody>()->AddCollisionShape(box->GetComponent<BoxCollider>()->GetCollisionShape());
	box2->GetComponent<RigidBody>()->AddCollisionShape(box2->GetComponent<BoxCollider>()->GetCollisionShape());
	box3->GetComponent<RigidBody>()->AddCollisionShape(box3->GetComponent<BoxCollider>()->GetCollisionShape());
	box4->GetComponent<RigidBody>()->AddCollisionShape(box4->GetComponent<BoxCollider>()->GetCollisionShape());
	box5->GetComponent<RigidBody>()->AddCollisionShape(box5->GetComponent<BoxCollider>()->GetCollisionShape());

	curuthers->GetComponent<RigidBody>()->AddTriggerCollisionShape(curuthers->GetComponent<BoxCollider>()->GetCollisionShape());
	finish->GetComponent<RigidBody>()->AddTriggerCollisionShape(finish->GetComponent<BoxCollider>()->GetCollisionShape());

	floor->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box2->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box3->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box4->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box5->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	finish->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	
	quad->GetTransform()->SetPosition(rend::vec3(0,35,-50));
	quad->GetTransform()->SetScale(rend::vec3(50));

	pickup->GetTransform()->SetPosition(rend::vec3(15, 17.5f, 0));
	pickup->GetTransform()->SetRotation(rend::vec3(0, -90, 0));
	pickup->GetTransform()->SetScale(rend::vec3(5));

	curuthers->GetTransform()->SetPosition(rend::vec3(0.0f, 5.0f, 0.0f));
	curuthers->GetTransform()->SetRotation(rend::vec3(0.0f, 90.0f, 0.0f));
	curuthers->GetTransform()->SetScale(rend::vec3(1.0f, 1.0f, 1.0f));

	floor->GetTransform()->SetPosition(rend::vec3(0.0f, -1.0f, 0.0f));
	floor->GetTransform()->SetScale(rend::vec3(100.0f, 1.0f, 100.0f));

	box->GetTransform()->SetPosition(rend::vec3(-5.0f, 10.0f, 0.0f));
	box->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box2->GetTransform()->SetPosition(rend::vec3(15.0f, 4.0f, 0.0f));
	box2->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box3->GetTransform()->SetPosition(rend::vec3(25.0f, 6.0f, 0.0f));
	box3->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box4->GetTransform()->SetPosition(rend::vec3(35.0f, 8.0f, 0.0f));
	box4->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box5->GetTransform()->SetPosition(rend::vec3(45.0f, 10.0f, 0.0f));
	box5->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	finish->GetTransform()->SetPosition(rend::vec3(45.0f, 12.0f, 0.0f));
	finish->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	curuthers->GetComponent<Controller>()->finish = finish;
	curuthers->GetComponent<Controller>()->pickup = pickup;

	core->Start();

	return 0;
}