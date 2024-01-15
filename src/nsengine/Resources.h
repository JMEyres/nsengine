#include<memory>
#include<vector>
#include<string>
//#include "Resource.h"

namespace nsengine
{
	struct Resource;
	struct Texture;
	/// @brief Class responsible for all resources
	struct Resources
	{
		/// @brief Load resource of specified type
		/// @tparam T Type of resource to load
		/// @param path Path the resource to load
		/// @return Pointer to loaded resource
		template <typename T>
		std::shared_ptr<T> Load(const std::string& _path)
		{
			for (size_t i = 0; i < resources.size(); ++i)
			{
				if (resources.at(i)->GetPath() == _path)
				{
					return std::dynamic_pointer_cast<T>(resources.at(i));
				}
			}

			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->resources = self;
			rtn->path = _path;
			rtn->Load();
			resources.push_back(rtn);

			return rtn;
		}

		/// @brief Load an animation from a directory
		/// @param path Path to directory
		/// @param frameCount Numebr of animation frames
		/// @return Vector of all textures in given directory used for animation
		std::vector<std::shared_ptr<Texture>> LoadAnimation(std::string _path, int _frameCount);

	private:
		friend struct Core;
		std::vector<std::shared_ptr<Resource> > resources;
		std::weak_ptr<Resources> self;
	};
}