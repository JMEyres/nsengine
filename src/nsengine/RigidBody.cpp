#include "RigidBody.h"

namespace nsengine
{
	void RigidBody::onTick()
	{
		std::vector<std::shared_ptr<BoxCollider>> boxColliders;
		getEntity()->getEnvironment()->getCore()->Find(boxColliders);
		std::shared_ptr<BoxCollider> box;

		box = getEntity()->getComponent<BoxCollider>();


		//btAlignedObjectArray <btCollisionShape*> collisionShapes;
		getEntity()->getEnvironment()->getCore()->collisionShapes;

		// dynamic rigidbody
		{
			btCollisionShape* colShape = new btSphereShape(btScalar(1.));
			getEntity()->getEnvironment()->getCore()->collisionShapes.push_back(colShape);

			btTransform startTransform;
			startTransform.setIdentity();

			btScalar mass(1.f);
			
			bool isDynamic = (mass != 0.f);

			btVector3 localInertia(0, 0, 0);

			if (isDynamic)
				colShape->calculateLocalInertia(mass, localInertia);

			startTransform.setOrigin(btVector3(2, 10, 0));

			btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
			btRigidBody* body = new btRigidBody(rbInfo);

			getEntity()->getEnvironment()->getCore()->dynamicsWorld->addRigidBody(body);
		}

		for (int i = 0; i < 150; ++i)
		{
			getEntity()->getEnvironment()->getCore()->dynamicsWorld->stepSimulation(1.f/60.f, 10);

			for (int j = getEntity()->getEnvironment()->getCore()->dynamicsWorld->getNumCollisionObjects() - 1; j > 0; --j)
			{
				btCollisionObject* obj = getEntity()->getEnvironment()->getCore()->dynamicsWorld->getCollisionObjectArray()[j];
				btRigidBody* body = btRigidBody::upcast(obj);
				btTransform trans;
				if (body && body->getMotionState())
				{
					body->getMotionState()->getWorldTransform(trans);
				}
				else
				{
					trans = obj->getWorldTransform();
				}
				printf("world pos object % d = % f, % f, % f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
			}
		}

		//remove the rigidbodies from the dynamics world and delete them
		for (int i = getEntity()->getEnvironment()->getCore()->dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = getEntity()->getEnvironment()->getCore()->dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			getEntity()->getEnvironment()->getCore()->dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}

		//delete collision shapes
		for (int j = 0; j < getEntity()->getEnvironment()->getCore()->collisionShapes.size(); j++)
		{
			btCollisionShape* shape = getEntity()->getEnvironment()->getCore()->collisionShapes[j];
			getEntity()->getEnvironment()->getCore()->collisionShapes[j] = 0;
			delete shape;
		}


		//next line is optional: it will be cleared by the destructor when the array goes out of scope
		getEntity()->getEnvironment()->getCore()->collisionShapes.clear();
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

	void RigidBody::onInitialize()
	{
		//btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.))); // box collider
		//getEntity()->getEnvironment()->getCore()->collisionShapes.push_back(groundShape); // push back to collision shapes
		btCollisionShape* collisionShape = getEntity()->getComponent<BoxCollider>()->collider;

		std::shared_ptr<Transform> objectTransform = getEntity()->getTransform();
		glm::vec3 objectPos = objectTransform->getPosition();
		btVector3 origin;
		
		origin.setValue(objectPos.x, objectPos.y, objectPos.z);

		btTransform rbTransform;
		rbTransform.setIdentity();
		rbTransform.setOrigin(origin);

		btScalar mass(mass); // pass in mass
		std::cout << mass << std::endl;

		bool isDynamic = (mass != 0.f); // defining if its dynamic
		
		//btVector3 localInertia(0, 0, 0); // potentially pass in
		
		if (isDynamic)
			collisionShape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(rbTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, collisionShape, localInertia); // defining rigidbody info with previous stats
		btRigidBody* body = new btRigidBody(rbInfo);

		getEntity()->getEnvironment()->getCore()->dynamicsWorld->addRigidBody(body);
	}
}