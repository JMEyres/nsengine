#include "Camera.h"

namespace nsengine
{
	void Camera::OnInitialize()
	{
		SetupCamera();

		GetEntity()->GetEnvironment()->AddCamera(std::static_pointer_cast<Camera>(self.lock())); // add camera to environment list
	}

	void Camera::OnTick()
	{
		UpdateCamera();
	}

	void Camera::SetupCamera()
	{
		// Set up the viewing matrix
		// This represents the camera's orientation and position
		viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		// Set up a projection matrix
		projMatrix = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 1500.0f);
	}

	void Camera::UpdateCamera()
	{
		viewMatrix = rend::inverse(GetEntity()->GetTransform()->Model());

		glm::vec3 pos = GetEntity()->GetTransform()->GetPosition();
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z); // set position of audio listener to camera position
	}

	void Camera::Follow()
	{
		float dt = GetCore()->GetDeltaTime();

		glm::vec2 oldMouse;

		glm::vec2 currentMouse = glm::vec2(GetCore()->GetInput()->GetMouseX(), GetCore()->GetInput()->GetMouseY());
		glm::vec2 mouseDelta = oldMouse - currentMouse;

		GetEntity()->GetTransform()->Rotate(mouseDelta.y * 0.075f, 0, 0); // rotate camera by mouse movements

		oldMouse = currentMouse;

		glm::vec3 camRot = GetEntity()->GetTransform()->GetRotation();

		follow = true;
		glm::vec3 pos = target->GetTransform()->GetPosition();
		glm::vec3 rot = target->GetTransform()->GetRotation();
		pos = pos + offset;
		GetEntity()->GetTransform()->SetPosition(pos);
		GetEntity()->GetTransform()->SetRotation(glm::vec3(camRot.x,rot.y+180,0)); // set camera to updated rotation

		glm::vec3 targetPos = target->GetTransform()->GetPosition() + glm::vec3(3,1,0);
		glm::vec3 cameraPos = GetEntity()->GetTransform()->GetPosition();
	}

	void Camera::SetTarget(std::shared_ptr<Entity> entity)
	{
		target = entity;
	}

	void Camera::SetOffset(float x, float y, float z)
	{
		offset = glm::vec3(x, y, z);
	}

	rend::mat4 Camera::GetView()
	{
		return viewMatrix;
	}
	rend::mat4 Camera::GetProj()
	{
		return projMatrix;
	}
}