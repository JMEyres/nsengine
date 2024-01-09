#pragma once
#include "Resource.h"

namespace nsengine
{
	struct Audio : Resource
	{
		void onLoad();
	private:
		//std::shared_ptr<Audiosource> texture;
	};
}