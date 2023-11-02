#pragma once
#include <memory>
#include <vector>
#include<type_traits>
#include<iostream>

namespace nsengine
{
	struct Core; // forward declare
	struct Component;
	struct Transform;

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

		std::shared_ptr<Core> getCore();

	private:
		friend struct Core;
		
		std::weak_ptr<Core> core; // core owns entities
		std::weak_ptr<Entity> self;
		std::weak_ptr<Transform> transform;

		bool alive;
		std::vector<std::shared_ptr<Component> > components; // List of components

		void initialize();
		void tick();
		void display();
	};
}