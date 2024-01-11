#pragma once
#include <rend/rend.h>
#include <AL/al.h>
#include <AL/alc.h>

#include "Component.h"
#include "Entity.h"

namespace nsengine
{
	struct Camera : Component
	{
	public:
		void onInitialize();
		void onTick();

		void SetupCamera();
		void UpdateCamera();

		void SetTarget(std::shared_ptr<Entity> entity);
		void SetOffset(float x, float y, float z);
		void Follow();

		glm::mat4 viewMatrix;
		glm::mat4 projMatrix;

		float cameraAngleX;
		float cameraAngleY;
	private:
		std::shared_ptr<Entity> target;
		glm::vec3 offset = glm::vec3(0);
		bool follow;
		glm::vec3 viewDirection;

	};
}