#include "Camera.h"

namespace nsengine
{
	void Camera::onInitialize()
	{
		SetupCamera();

		getEntity()->getEnvironment()->addCamera(std::static_pointer_cast<Camera>(self.lock()));
	}

	void Camera::onTick()
	{
		//Follow();
		UpdateCamera();
	}

	void Camera::SetupCamera()
	{
		cameraAngleX = 0.0f, cameraAngleY = 0.0f;

		// Set up the viewing matrix
		// This represents the camera's orientation and position
		viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		// Set up a projection matrix
		projMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	}

	void Camera::UpdateCamera()
	{
		if(!follow)
			viewMatrix = rend::inverse(getEntity()->getTransform()->Model());

		glm::vec3 pos = getEntity()->getTransform()->getPosition();
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	}

	void Camera::Follow()
	{
		follow = true;
		glm::vec3 pos = target->getTransform()->getPosition();
		glm::vec3 rot = target->getTransform()->getRotation();
		pos = pos + offset;
		getEntity()->getTransform()->setPosition(pos);

		glm::vec3 targetPos = target->getTransform()->getPosition() + glm::vec3(3,1,0);
		glm::vec3 cameraPos = getEntity()->getTransform()->getPosition();
		viewMatrix = glm::lookAt(cameraPos, targetPos, glm::vec3(0, 1, 0));
	}

	void Camera::SetTarget(std::shared_ptr<Entity> entity)
	{
		target = entity;
	}

	void Camera::SetOffset(float x, float y, float z)
	{
		offset = glm::vec3(x, y, z);
	}
}