#include "Resource.h"
#include "Resources.h"

namespace nsengine
{
	void Resource::Load() { OnLoad(); }

	std::string Resource::GetPath() 
	{ 
		cwd = cwd + "/Resources"; // get the current working directory and add resources on end
		std::string fullPath = cwd + path;
		return fullPath;
	}
}