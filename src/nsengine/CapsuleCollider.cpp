#include "CapsuleCollider.h"
#include "Entity.h"

namespace nsengine
{
	void CapsuleCollider::CreateCollider(float radius, float height)
	{
		capsule = GetCore()->physicsCommon.createCapsuleShape(radius, height); // create capsule collider by radius and height
	}

	rp3d::CapsuleShape* CapsuleCollider::GetCollisionShape()
	{
		return capsule;
	}
}