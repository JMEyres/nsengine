#include <nsengine/nsengine.h>
#include "blocks.h"
#include "controller.h"
#include "cameracontroller.h"

using namespace nsengine;

#undef main // SDL2 Wraps everything in its own main so causes a linker error, this stops it looking for that undefines it

int main()
{
	std::shared_ptr<Core> core = Core::Initialize(); // initializes core

	std::shared_ptr<Environment> environment = core->CreateEnvironment();

	std::shared_ptr<Entity> curuthers = environment->AddEntity();
	std::shared_ptr<Entity> quad = environment->AddEntity(); // creating entity, core holds on list
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

	pickup->AddComponent<AudioSource>();
	pickup->GetComponent<AudioSource>()->SetAudio(pickup->GetEnvironment()->GetCore()->GetResources()->Load<Audio>("/Audio/pickup.ogg"));

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

	curuthers->AddComponent<CapsuleCollider>();
	curuthers->GetComponent<CapsuleCollider>()->CreateCollider(1.0f, 1.0f);

	curuthers->AddComponent<BoxCollider>();
	curuthers->GetComponent<BoxCollider>()->CreateCollider(10.0f, 10.0f, 10.0f);

	pickup->AddComponent<BoxCollider>();
	pickup->GetComponent<BoxCollider>()->CreateCollider(1.0f, 1.0f, 1.0f);

	finish->AddComponent<BoxCollider>();
	finish->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);

	curuthers->AddComponent<RigidBody>();
	pickup->AddComponent<RigidBody>();
	finish->AddComponent<RigidBody>();

	curuthers->GetComponent<Renderer>()->SetPath("/Models/curuthers.obj");
	
	curuthers->GetComponent<RigidBody>()->AddCollisionShape(curuthers->GetComponent<CapsuleCollider>()->GetCollisionShape());
	pickup->GetComponent<RigidBody>()->AddCollisionShape(pickup->GetComponent<BoxCollider>()->GetCollisionShape());

	curuthers->GetComponent<RigidBody>()->AddTriggerCollisionShape(curuthers->GetComponent<BoxCollider>()->GetCollisionShape());
	finish->GetComponent<RigidBody>()->AddTriggerCollisionShape(finish->GetComponent<BoxCollider>()->GetCollisionShape());

	pickup->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	finish->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	
	quad->GetTransform()->SetPosition(rend::vec3(0,35,-150));
	quad->GetTransform()->SetScale(rend::vec3(50));

	pickup->GetTransform()->SetPosition(rend::vec3(90, 17.5f, -20));
	pickup->GetTransform()->SetRotation(rend::vec3(0, -90, 0));
	pickup->GetTransform()->SetScale(rend::vec3(5));

	curuthers->GetTransform()->SetPosition(rend::vec3(0.0f, 5.0f, 0.0f));
	curuthers->GetTransform()->SetRotation(rend::vec3(0.0f, 90.0f, 0.0f));
	curuthers->GetTransform()->SetScale(rend::vec3(1.0f, 1.0f, 1.0f));

	finish->GetTransform()->SetPosition(rend::vec3(170.0f, 12.0f, 0.0f));
	finish->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	curuthers->GetComponent<Controller>()->finish = finish;
	curuthers->GetComponent<Controller>()->pickup = pickup;

	CreateBlocks(environment);

	core->Start();

	return 0;
}