#pragma once
#include <rend/rend.h>
#include "Component.h"
#include "Entity.h"

namespace nsengine
{
	struct Camera;
	struct Gui : Component
	{
		void onLoad();
		void onDisplay();
	};
}