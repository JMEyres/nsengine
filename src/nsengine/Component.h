#pragma once
#ifndef NSENGINE_COMPONENT_H
#define NSENGINGE_COMPONENT_H

#include <memory>
#include "Entity.h"

namespace nsengine
{
	struct Entity; // forward declare entity

	struct Component
	{
	public:
		virtual void onTick();
		virtual void onDisplay();

		std::shared_ptr<Entity> getEntity();

	private:
		friend struct Entity;

		std::weak_ptr<Entity> entity; // entity owns component object

		void tick();
		void display();
	};
}

#endif // !NSENGINE_COMPONENT_H