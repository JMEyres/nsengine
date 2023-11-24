#pragma once
#include "Resource.h"

namespace nsengine
{
	struct Model : Resource
	{
		void onLoad();

	private:
		std::shared_ptr<rend::Model> model;
	};
}