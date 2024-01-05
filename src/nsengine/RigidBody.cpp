#include "RigidBody.h"
#include <ReactPhysics3D/include/reactphysics3d/reactphysics3d.h>

namespace nsengine
{
	void RigidBody::onTick()
	{
		std::vector<std::shared_ptr<BoxCollider>> boxColliders;
		getEntity()->getEnvironment()->getCore()->Find(boxColliders);
		std::shared_ptr<BoxCollider> box;

		box = getEntity()->getComponent<BoxCollider>();

		for(size_t bci = 0; bci < boxColliders.size(); ++bci)
		{
			if (boxColliders.at(bci)->getEntity() == getEntity())
				continue;

			if (box)
				if (boxColliders.at(bci)->isColliding(box->getEntity()->getTransform()->getPosition(), glm::vec3(2)))
				{
					getEntity()->getTransform()->setPosition(box->getCollisionResponse(
						box->getEntity()->getTransform()->getPosition(), glm::vec3(0)));
				}
		}
	}
}