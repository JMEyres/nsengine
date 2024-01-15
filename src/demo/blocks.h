#include <nsengine/nsengine.h>
using namespace nsengine;

inline std::shared_ptr<Entity> MakeBlock(std::shared_ptr<Environment> _environment)
{
	std::shared_ptr<Entity> block = _environment->AddEntity();
	block->AddComponent<Renderer>();
	block->AddComponent<BoxCollider>();
	block->AddComponent<RigidBody>();

	return block;
}

inline void CreateBlocks(std::shared_ptr<Environment> _environment)
{
	std::shared_ptr<Entity> floor = MakeBlock(_environment);
	std::shared_ptr<Entity> box = MakeBlock(_environment);
	std::shared_ptr<Entity> box2 = MakeBlock(_environment);
	std::shared_ptr<Entity> box3 = MakeBlock(_environment);
	std::shared_ptr<Entity> box4 = MakeBlock(_environment);
	std::shared_ptr<Entity> box5 = MakeBlock(_environment);

	floor->GetComponent<BoxCollider>()->CreateCollider(250.0f, 1.0f, 250.0f);
	box->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);
	box2->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);
	box3->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);
	box4->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);
	box5->GetComponent<BoxCollider>()->CreateCollider(5.0f, 11.0f, 5.0f);

	floor->GetComponent<RigidBody>()->SetBounciness(0.9f); // Make floor bouncy

	floor->GetComponent<Renderer>()->SetPath("/Models/floor.obj");
	box->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");
	box2->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");
	box3->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");
	box4->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");
	box5->GetComponent<Renderer>()->SetPath("/Models/Cube.obj");

	floor->GetComponent<RigidBody>()->AddCollisionShape(floor->GetComponent<BoxCollider>()->GetCollisionShape());
	box->GetComponent<RigidBody>()->AddCollisionShape(box->GetComponent<BoxCollider>()->GetCollisionShape());
	box2->GetComponent<RigidBody>()->AddCollisionShape(box2->GetComponent<BoxCollider>()->GetCollisionShape());
	box3->GetComponent<RigidBody>()->AddCollisionShape(box3->GetComponent<BoxCollider>()->GetCollisionShape());
	box4->GetComponent<RigidBody>()->AddCollisionShape(box4->GetComponent<BoxCollider>()->GetCollisionShape());
	box5->GetComponent<RigidBody>()->AddCollisionShape(box5->GetComponent<BoxCollider>()->GetCollisionShape());

	floor->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box2->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box3->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box4->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);
	box5->GetComponent<RigidBody>()->SetType(rp3d::BodyType::STATIC);

	floor->GetTransform()->SetPosition(rend::vec3(0.0f, -1.0f, 0.0f));
	floor->GetTransform()->SetScale(rend::vec3(500.0f, 1.0f, 500.0f));

	box->GetTransform()->SetPosition(rend::vec3(30.0f, 2.0f, 0.0f));
	box->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box2->GetTransform()->SetPosition(rend::vec3(60.0f, 5.0f, 20.0f));
	box2->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box3->GetTransform()->SetPosition(rend::vec3(90.0f, 5.0f, -20.0f));
	box3->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box4->GetTransform()->SetPosition(rend::vec3(120.0f, 8.0f, 0.0f));
	box4->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));

	box5->GetTransform()->SetPosition(rend::vec3(170.0f, 10.0f, 0.0f));
	box5->GetTransform()->SetScale(rend::vec3(10.0f, 10.0f, 10.0f));
}