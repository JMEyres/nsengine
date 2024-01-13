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
		projMatrix = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 1500.0f);
	}

	void Camera::UpdateCamera()
	{
		//if(!follow)
			viewMatrix = rend::inverse(getEntity()->getTransform()->Model());

		glm::vec3 pos = getEntity()->getTransform()->getPosition();
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	}

	void Camera::Follow()
	{
		float dt = getCore()->getDeltaTime();

		glm::vec2 oldMouse;

		glm::vec2 currentMouse = glm::vec2(getCore()->getInput()->mouseX, getCore()->getInput()->mouseY);
		glm::vec2 mouseDelta = oldMouse - currentMouse;

		getEntity()->getTransform()->Rotate(mouseDelta.y * 0.075f, 0, 0);

		oldMouse = currentMouse;

		glm::vec3 camRot = getEntity()->getTransform()->getRotation();

		follow = true;
		glm::vec3 pos = target->getTransform()->getPosition();
		glm::vec3 rot = target->getTransform()->getRotation();
		pos = pos + offset;
		getEntity()->getTransform()->setPosition(pos);
		getEntity()->getTransform()->setRotation(glm::vec3(camRot.x,rot.y+180,0));

		glm::vec3 targetPos = target->getTransform()->getPosition() + glm::vec3(3,1,0);
		glm::vec3 cameraPos = getEntity()->getTransform()->getPosition();
		//viewMatrix = glm::lookAt(cameraPos, targetPos, glm::vec3(0, 1, 0));
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