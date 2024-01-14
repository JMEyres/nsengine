#include "Resource.h"
#include "Resources.h"

namespace nsengine
{
	void Resource::load() { onLoad(); }

	std::string Resource::getPath() 
	{ 
		cwd = cwd + "/Resources";
		std::string fullPath = cwd + path;
		return fullPath;
	}
}