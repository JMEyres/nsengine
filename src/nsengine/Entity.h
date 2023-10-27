#pragma once
#include <memory>
#include <vector>

namespace nsengine
{
	struct Core; // forward declare
	struct Component;

	struct Entity
	{
		template <typename T>
		std::shared_ptr<T> addComponent() // constructing addComponent
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->entity = self;

			components.push_back(rtn);

			return rtn;
		}

		std::shared_ptr<Core> getCore();

	private:
		friend struct Core;
		
		std::weak_ptr<Core> core; // core owns entities
		std::weak_ptr<Entity> self; // core owns entities

		bool alive;
		std::vector<std::shared_ptr<Component> > components; // List of components

		void initialize();
		void tick();
		void display();
	};
}