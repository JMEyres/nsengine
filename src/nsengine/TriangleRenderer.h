#include "Component.h"
#include <iostream>
#include <rend/rend.h>
#include "nsengine/Transform.h"

namespace nsengine
{
	struct TriangleRenderer : Component
	{
	private:
		rend::Mesh mesh;
		rend::Shader shader;

		void onInitialize();
		void onDisplay();
	};
}