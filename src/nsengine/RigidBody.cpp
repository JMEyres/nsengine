#include "RigidBody.h"

namespace nsengine
{
	void RigidBody::setType(rp3d::BodyType type)
	{
		rbType = type;
	}

	void RigidBody::onPhysicsTick()
	{
		rp3d::Transform transform = rb->getTransform();

		rp3d::Vector3 position = transform.getPosition();

		glm::vec3 newPos = glm::vec3(position.x, position.y, position.z);

		getEntity()->getTransform()->setPosition(newPos);

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
		rb->setType(rbType);
		collider = rb->addCollider(getEntity()->getComponent<BoxCollider>()->box, rp3d::Transform::identity()); // Collider has to have a separate transform because its local. - this is what you would use to offset collider from object
	}
}