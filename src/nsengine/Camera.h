#pragma once
#include <rend/rend.h>
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

		glm::mat4 viewMatrix;
		glm::mat4 projMatrix;

		float cameraAngleX;
		float cameraAngleY;
	private:
	};
}