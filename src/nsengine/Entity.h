#pragma once
#include <memory>
#include <vector>
#include <type_traits>
#include <iostream>

#include "Component.h"
#include "Core.h"

namespace nsengine
{
	struct Core; // forward declare
	struct Environment;
	struct Component;
	struct Transform;
	struct RigidBody;

	struct Entity
	{
		template <typename T>
		std::shared_ptr<T> addComponent() // constructing addComponent
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->entity = self;
			rtn->self = rtn;

			components.push_back(rtn);

			return rtn;
		}

		template <typename c>
		std::shared_ptr<c> getComponent()
		{
			for (size_t ci = 0; ci < components.size(); ++ci)
			{
				std::shared_ptr<c> rtn = std::dynamic_pointer_cast<c>(components.at(ci));

				if (rtn) return rtn;
			}
		}

		std::shared_ptr<Transform> getTransform();
		std::shared_ptr<Environment> getEnvironment();

	private:
		friend struct Core;
		friend struct Environment;
		
		std::weak_ptr<Environment> environment;
		std::weak_ptr<Entity> self;
		std::weak_ptr<Transform> transform;

		bool alive;
		std::vector<std::shared_ptr<Component> > components; // List of components

		void initialize();
		void tick();
		void physicsTick();
		void display();
	};
}