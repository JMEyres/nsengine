#include "BoxCollider.h"
#include "Entity.h"

namespace nsengine
{
	void BoxCollider::createCollider(float x, float y, float z)
	{
		size = rp3d::Vector3(x, y, z);
		box = getCore()->physicsCommon.createBoxShape(size);
	}
}