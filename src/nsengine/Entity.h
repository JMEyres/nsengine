#include <memory>

namespace nsengine
{
	struct Component;

	struct Entity
	{
		std::shared_ptr<Component> addComponent(); // constructing addComponent

	private:
		std::vector<std::shared_ptr<Component> > components; // List of components
	};
}