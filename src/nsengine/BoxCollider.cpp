#include "BoxCollider.h"
#include "Entity.h"

namespace nsengine
{
	bool BoxCollider::isColliding(glm::vec3 otherPos, glm::vec3 otherSize)
	{
		glm::vec3 a = getEntity()->getTransform()->getPosition();
		glm::vec3 b = otherPos;
		glm::vec3 ahs = size / 2.0f;
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

	glm::vec3 BoxCollider::getCollisionResponse(glm::vec3 pos, glm::vec3 size)
	{
		float amount = 0.2f; // want this to be equal to the size of the box so it moves to the edge automatically, might need the position difference sorta thang
		float step = 0.2f;

		while (true)
		{
			if (!isColliding(pos, size)) break;
			pos.x += amount;
			if (!isColliding(pos, size)) break;
			pos.x -= amount;
			pos.x -= amount;
			if (!isColliding(pos, size)) break;
			pos.x += amount;
			pos.z += amount;
			if (!isColliding(pos, size)) break;
			pos.z -= amount;
			pos.z -= amount;
			if (!isColliding(pos, size)) break;
			pos.z += amount;
			pos.y += amount;
			if (!isColliding(pos, size)) break;
			pos.y -= amount;
			pos.y -= amount;
			if (!isColliding(pos, size)) break;
			pos.y += amount;
			amount += step;
		}
		return pos;
	}

	void BoxCollider::onInitialize()
	{
		box = getCore()->physicsCommon.createBoxShape(rp3d::Vector3(1,1,1));
	}
}