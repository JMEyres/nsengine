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

int main()
{
	std::shared_ptr<Core> core = Core::initialize(); // initializes core

	std::shared_ptr<Environment> environment = core->createEnvironment();
	std::shared_ptr<Entity> entity = environment->addEntity(); // creating entity, core holds on list
	std::shared_ptr<Texture> texture = core->getResources()->load<Texture>("src/Resources/Textures/canosprite.png");
	//std::shared_ptr<Model> texture = core->getResources()->load<Model>("src/Resources/Textures/canosprite.png");
	entity->addComponent<Player>(); // creating component, entity holds on list
	entity->addComponent<TriangleRenderer>(); // creating component, entity holds on list

	
	entity->getTransform()->setPosition(rend::vec3(0.0f, 0.0f, -5.0f));
	entity->getTransform()->setScale(rend::vec3(1.0f, 1.0f, 1.0f));

	core->start();

	return 0;
}