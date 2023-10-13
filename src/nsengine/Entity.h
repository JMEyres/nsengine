#pragma once
#include <memory>
#include <list>

namespace nsengine
{
	struct Component;

	struct Entity
	{
		std::shared_ptr<Component> addComponent(); // constructing addComponent

	private:
		friend struct core;
		std::list<std::shared_ptr<Component> > components; // List of components
	};
}