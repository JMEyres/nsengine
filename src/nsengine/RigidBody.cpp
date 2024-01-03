#include "RigidBody.h"

namespace nsengine
{
	void RigidBody::onTick()
	{
		std::vector<std::shared_ptr<BoxCollider>> boxColliders;
		getEntity()->getEnvironment()->getCore()->Find(boxColliders);
	}
}