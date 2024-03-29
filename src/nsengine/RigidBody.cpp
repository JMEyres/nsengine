#include "RigidBody.h"

namespace nsengine
{
	void RigidBody::SetType(rp3d::BodyType _type)
	{
		rbType = _type;
	}

	void RigidBody::AddCollisionShape(rp3d::CollisionShape* _shape)
	{
		collisionShape = _shape;
	}
	void RigidBody::AddTriggerCollisionShape(rp3d::CollisionShape* _shape)
	{
		isTrigger = true;
		triggerCollisionShape = _shape;
	}
	void RigidBody::Disable()
	{
		disable = true;
		SetPosition(0, -1000, 0);
	}

	void RigidBody::Enable()
	{
		disable = false;
		SetPosition(originalPosition.x, originalPosition.y, originalPosition.z);
	}

	void RigidBody::SetBounciness(float _value)
	{
		_value = rend::fclamp(_value, 0.0f, 1.0f);
		bounciness = _value;
	}

	void RigidBody::Move(float _x, float _y, float _z)
	{
		rend::vec3 movement = GetEntity()->GetTransform()->Model() * rend::vec4(_x, _y, _z, 0);

		rb->applyLocalForceAtCenterOfMass(rp3d::Vector3(movement.x, movement.y, movement.z)); // apply movement by simulated forces

	}

	void RigidBody::SetPosition(float _x, float _y, float _z)
	{
		rp3d::Transform transform = rb->getTransform();
		transform.setPosition(rp3d::Vector3(_x, _y, _z)); // force set rigidbody pos
		rb->setTransform(transform);
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

		rend::vec3 newPos = rend::vec3(position.x, position.y, position.z);

		GetEntity()->GetTransform()->SetPosition(newPos); // set entity transform to simulated physics position
	}

	void RigidBody::OnInitialize()
	{
		rp3d::Transform transform;
		rend::vec3 pos = GetEntity()->GetTransform()->GetPosition();
		rp3d::Vector3 physicsPos = rp3d::Vector3(pos.x, pos.y, pos.z);
		originalPosition = physicsPos;

		transform.setPosition(physicsPos);

		rb = GetCore()->physicsWorld->createRigidBody(transform); // create rigidbody
		rb->setType(rbType); // set the type of rigidbody, defaulted to dynamic
		rb->enableGravity(true); // enable gravity on rigid body
		rb->setMass(1); // set mass of rigid body
		rb->setAngularLockAxisFactor(rp3d::Vector3(0, 0, 0)); // stop rigid body rotating so characters dont roll
		if(collisionShape)
		{
			collider = rb->addCollider(collisionShape, rp3d::Transform::identity()); // Collider has to have a separate transform because its local. - this is what you would use to offset collider from object
			rp3d::Material& mat = collider->getMaterial();
			mat.setBounciness(bounciness); // set the bounciness of the rigid body, 0 not bouncy 1 will infinitely bounce
		}

		if (isTrigger)
		{
			triggerCollider = rb->addCollider(triggerCollisionShape, rp3d::Transform::identity()); // add trigger collision shape for collision events
			triggerCollider->setIsTrigger(isTrigger);
		}
	}

	rp3d::RigidBody* RigidBody::GetRigidBody()
	{
		return rb;
	}
}