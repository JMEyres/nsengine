#pragma once
#include <memory>

namespace nsengine
{
	struct Entity; // forward declare entity
	struct Core;

	struct Component
	{
	public:
		virtual void onInitialize();
		virtual void onTick();
		virtual void onPhysicsTick();
		virtual void onDisplay();

		std::shared_ptr<Entity> getEntity();
		std::shared_ptr<Core> getCore();

		std::weak_ptr<Core> core;
	private:
		friend struct Entity;

		std::weak_ptr<Entity> entity; // entity owns component object
		std::weak_ptr<Component> self; // entity owns component object

		void initialize();
		void tick();
		void physicsTick();
		void display();
	};
}