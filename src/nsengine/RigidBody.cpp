#include "RigidBody.h"

namespace nsengine
{
	void RigidBody::SetType(rp3d::BodyType type)
	{
		rbType = type;
	}

	void RigidBody::AddCollisionShape(rp3d::CollisionShape* shape)
	{
		collisionShape = shape;
	}
	void RigidBody::AddTriggerCollisionShape(rp3d::CollisionShape* shape)
	{
		isTrigger = true;
		triggerCollisionShape = shape;
	}
	void RigidBody::Disable()
	{
		disable = true;
		Move(0, -100000, 0);
	}

	void RigidBody::SetBounciness(float value)
	{
		value = glm::fclamp(value, 0.0f, 1.0f);
		bounciness = value;
	}

	void RigidBody::Move(float x, float y, float z)
	{
		rend::vec3 movement = GetEntity()->GetTransform()->Model() * rend::vec4(x, y, z, 0);

		rb->applyLocalForceAtCenterOfMass(rp3d::Vector3(movement.x, movement.y, movement.z));

	}
	rend::vec3 RigidBody::GetPos()
	{
		rp3d::Transform transform = rb->getTransform();

		rp3d::Vector3 position = transform.getPosition();
		
		rend::vec3 pos = rend::vec3(position.x, position.y, position.z);
		return pos;
	}
	void RigidBody::OnPhysicsTick()
	{
		rp3d::Transform transform = rb->getTransform();

		rp3d::Vector3 position = transform.getPosition();

		glm::vec3 newPos = glm::vec3(position.x, position.y, position.z);

		GetEntity()->GetTransform()->SetPosition(newPos);
	}

	void RigidBody::OnInitialize()
	{
		rp3d::Transform transform;
		glm::vec3 pos = GetEntity()->GetTransform()->GetPosition();
		rp3d::Vector3 physicsPos = rp3d::Vector3(pos.x, pos.y, pos.z);

		transform.setPosition(physicsPos);

		rb = GetCore()->physicsWorld->createRigidBody(transform);
		rb->setType(rbType);
		rb->enableGravity(true);
		rb->setMass(1);
		rb->setAngularLockAxisFactor(rp3d::Vector3(0, 0, 0));
		if(collisionShape)
		{
			collider = rb->addCollider(collisionShape, rp3d::Transform::identity()); // Collider has to have a separate transform because its local. - this is what you would use to offset collider from object
			rp3d::Material& mat = collider->getMaterial();
			mat.setBounciness(bounciness);
		}

		if (isTrigger)
		{
			triggerCollider = rb->addCollider(triggerCollisionShape, rp3d::Transform::identity());
			triggerCollider->setIsTrigger(isTrigger);
		}
	}

	rp3d::RigidBody* RigidBody::GetRigidBody()
	{
		return rb;
	}
}