#include "Resource.h"
#include "Resources.h"

namespace nsengine
{
	void Resource::Load() { OnLoad(); }

	std::string Resource::GetPath() 
	{ 
		cwd = cwd + "/Resources";
		std::string fullPath = cwd + path;
		return fullPath;
	}
}