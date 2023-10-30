#include "Component.h"
#include <rend/rend.h>
#include<memory>

namespace nsengine
{
	struct Transform : Component
	{
		rend::vec3 position;
		rend::vec3 rotation;
		rend::vec3 scale;

		rend::mat4 Rotate(rend::mat4, float, rend::vec3);
		void Model();
	};
}