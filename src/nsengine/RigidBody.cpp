#include "RigidBody.h"

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
				if (boxColliders.at(bci)->Colliding(*box))
					std::cout << "HIT" << std::endl;
		}
	}
}