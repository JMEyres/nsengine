#include "RigidBody.h"

namespace nsengine
{
	void RigidBody::setType(rp3d::BodyType type)
	{
		rbType = type;
	}

	void RigidBody::addCollisionShape(rp3d::CollisionShape* shape)
	{
		collisionShape = shape;
	}

	void RigidBody::move(float x, float y, float z)
	{
		rend::vec3 movement = getEntity()->getTransform()->Model() * rend::vec4(x, y, z, 0);

		rb->applyLocalForceAtCenterOfMass(rp3d::Vector3(movement.x, movement.y, movement.z));

	}

	void RigidBody::rotate(float x, float y, float z)
	{
		//rp3d::Vector3 newRotation += rp3d::Vector3(x, y, z);
	}

	void RigidBody::onPhysicsTick()
	{
		rp3d::Transform transform = rb->getTransform();

		rp3d::Vector3 position = transform.getPosition();

		glm::vec3 newPos = glm::vec3(position.x, position.y, position.z);

		getEntity()->getTransform()->setPosition(newPos);
	}

	void RigidBody::onInitialize()
	{
		rp3d::Transform transform;
		glm::vec3 pos = getEntity()->getTransform()->getPosition();
		rp3d::Vector3 physicsPos = rp3d::Vector3(pos.x, pos.y, pos.z);

		transform.setPosition(physicsPos);

		rb = getCore()->physicsWorld->createRigidBody(transform);
		rb->setType(rbType);
		rb->enableGravity(true);
		rb->setMass(1);
		rb->setAngularLockAxisFactor(rp3d::Vector3(0, 0, 0));
		std::cout << collisionShape->to_string() << std::endl;
		collider = rb->addCollider(collisionShape, rp3d::Transform::identity()); // Collider has to have a separate transform because its local. - this is what you would use to offset collider from object
		rp3d::Material& mat = collider->getMaterial();
		mat.setBounciness(0);
	}
}