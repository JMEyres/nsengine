#pragma once
#include <memory>

namespace nsengine
{
	struct Entity; // forward declare entity

	struct Component
	{
	public:
		virtual void onInitialize();
		virtual void onTick();
		virtual void onDisplay();

		std::shared_ptr<Entity> getEntity();

	private:
		friend struct Entity;

		std::weak_ptr<Entity> entity; // entity owns component object
		std::weak_ptr<Component> self; // entity owns component object

		void initialize();
		void tick();
		void display();
	};
}