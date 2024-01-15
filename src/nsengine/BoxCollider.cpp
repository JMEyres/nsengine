#include "BoxCollider.h"
#include "Entity.h"

namespace nsengine
{
	bool BoxCollider::IsColliding(glm::vec3 otherPos, glm::vec3 otherSize)
	{
		glm::vec3 thisSize = glm::vec3(size.x, size.y, size.z);
		glm::vec3 a = GetEntity()->GetTransform()->GetPosition();
		glm::vec3 b = otherPos;
		glm::vec3 ahs = thisSize / 2.0f;
		glm::vec3 bhs = otherSize / 2.0f;

		if (a.x > b.x)
		{
			if (b.x + bhs.x < a.x - ahs.x)
				return false;
		}
		else
		{
			if (a.x + ahs.x < b.x - bhs.x)
				return false;
		}

		if (a.y > b.y)
		{
			if (b.y + bhs.y < a.y - ahs.y)
				return false;
		}
		else
		{
			if (a.y + ahs.y < b.y - bhs.y)
				return false;
		}

		if (a.z > b.z)
		{
			if (b.z + bhs.z < a.z - ahs.z)
				return false;
		}
		else
		{
			if (a.z + ahs.z < b.z - bhs.z)
				return false;
		}
	}

	rend::vec3 BoxCollider::GetSize()
	{
		return rend::vec3(size.x, size.y, size.z);
	}

	void BoxCollider::CreateCollider(float x, float y, float z)
	{
		size = rp3d::Vector3(x, y, z);
		box = GetCore()->physicsCommon.createBoxShape(size);
	}

	rp3d::BoxShape* BoxCollider::GetCollisionShape()
	{
		return box;
	}
}