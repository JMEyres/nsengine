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
		
	

		//remove the rigidbodies from the dynamics world and delete them
		//for (int i = getEntity()->getEnvironment()->getCore()->dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		//{
		//	btCollisionObject* obj = getEntity()->getEnvironment()->getCore()->dynamicsWorld->getCollisionObjectArray()[i];
		//	btRigidBody* body = btRigidBody::upcast(obj);
		//	if (body && body->getMotionState())
		//	{
		//		delete body->getMotionState();
		//	}
		//	getEntity()->getEnvironment()->getCore()->dynamicsWorld->removeCollisionObject(obj);
		//	delete obj;
		//}
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
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}
		else
		{
			trans = body->getWorldTransform();
		}

		printf("world pos object = % f, % f, % f\n", float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}

	void RigidBody::onInitialize()
	{
		btCollisionShape* collisionShape = getEntity()->getComponent<BoxCollider>()->collider;

		std::shared_ptr<Transform> objectTransform = getEntity()->getTransform();
		glm::vec3 objectPos = objectTransform->getPosition();
		btVector3 origin;
		
		origin.setValue(objectPos.x, objectPos.y, objectPos.z);

		btTransform rbTransform;
		rbTransform.setIdentity();
		rbTransform.setOrigin(origin);

		btScalar mass(mass); // pass in mass

		bool isDynamic = (mass != 0.f); // defining if its dynamic basically only thing that changes it is mass
		
		if (isDynamic)
			collisionShape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(rbTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, collisionShape, localInertia); // defining rigidbody info with previous stats
		body = new btRigidBody(rbInfo);

		getEntity()->getEnvironment()->getCore()->dynamicsWorld->addRigidBody(body);
	}
}