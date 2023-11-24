#include "Resource.h"
#include "Resources.h"

namespace nsengine
{
	void Resource::load() { onLoad(); }

	std::string Resource::getPath() { return path; }
}