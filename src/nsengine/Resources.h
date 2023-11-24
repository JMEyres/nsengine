#include<memory>
#include<vector>
#include<string>
//#include "Resource.h"

namespace nsengine
{
	struct Resource;
	struct Resources
	{
		template <typename T>
		std::shared_ptr<T> load(const std::string& path)
		{
			for (size_t i = 0; i < resources.size(); ++i)
			{
				if (resources.at(i)->getPath() == path)
				{
					return std::dynamic_pointer_cast<T>(resources.at(i));
				}
			}

			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->resources = self;
			rtn->path = path;
			rtn->load();
			resources.push_back(rtn);

			return rtn;
		}

	private:
		friend struct Core;
		std::vector<std::shared_ptr<Resource> > resources;
		std::weak_ptr<Resources> self;
	};
}