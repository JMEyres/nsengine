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
		viewMatrix = rend::inverse(getEntity()->getTransform()->Model());
	}
}