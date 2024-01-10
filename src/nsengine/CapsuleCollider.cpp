#include "CapsuleCollider.h"
#include "Entity.h"

namespace nsengine
{
	void CapsuleCollider::createCollider(float radius, float height)
	{
		capsule = getCore()->physicsCommon.createCapsuleShape(radius, height);
	}
}