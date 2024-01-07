#include "RigidBody.h"

namespace nsengine
{
	void RigidBody::onTick()
	{

		//std::vector<std::shared_ptr<BoxCollider>> boxColliders;
		//getEntity()->getEnvironment()->getCore()->Find(boxColliders);
		//std::shared_ptr<BoxCollider> box;
		//
		//box = getEntity()->getComponent<BoxCollider>();
		//
		//for(size_t bci = 0; bci < boxColliders.size(); ++bci)
		//{
		//	if (boxColliders.at(bci)->getEntity() == getEntity())
		//		continue;
		//
		//	if (box)
		//		if (boxColliders.at(bci)->isColliding(box->getEntity()->getTransform()->getPosition(), glm::vec3(2)))
		//		{
		//			getEntity()->getTransform()->setPosition(box->getCollisionResponse(
		//				box->getEntity()->getTransform()->getPosition(), glm::vec3(0)));
		//		}
		//}
	}

	void RigidBody::onPhysicsTick()
	{
		std::vector<std::shared_ptr<BoxCollider>> boxColliders;
		getCore()->Find(boxColliders);
		std::shared_ptr<BoxCollider> box; 

		box = getEntity()->getComponent<BoxCollider>();

		glm::vec3 newPos = getEntity()->getTransform()->getPosition();

		rp3d::Vector3 position = rp3d::Vector3(newPos.x,newPos.y, newPos.z);

		for (size_t bci = 0; bci < boxColliders.size(); ++bci)
		{
			std::cout << "TEST" << std::endl;
			if (boxColliders.at(bci)->getEntity() == getEntity())
				continue;

			if (box)
			{
				//rp3d::AABB colAabb = boxColliders.at(bci)->getEntity()->getComponent<RigidBody>()->rb->getAABB();
				//if (aabb.testCollision(colAabb))
				//{
				//	std::cout << "HIT" << std::endl;
				//}
			}
		}
		
		

		//std::cout << "Body Position: (" << position.x << ", " <<
		//	position.y << ", " << position.z << ")" << std::endl;
	}

	void RigidBody::onInitialize()
	{
		rp3d::Transform transform;
		glm::vec3 pos = getEntity()->getTransform()->getPosition();
		rp3d::Vector3 physicsPos = rp3d::Vector3(pos.x, pos.y, pos.z);
		

		transform.setPosition(physicsPos);
		rb = getCore()->physicsWorld->createRigidBody(transform);
		rb->setMass(0);
		collider = rb->addCollider(getEntity()->getComponent<BoxCollider>()->box, transform);
	}
}