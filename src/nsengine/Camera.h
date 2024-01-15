#pragma once
#include <rend/rend.h>
#include <AL/al.h>
#include <AL/alc.h>

#include "Component.h"
#include "Entity.h"

namespace nsengine
{
	/// @brief Camera component controlling the view the user sees
	struct Camera : Component
	{
	public:
		void OnInitialize();
		void OnTick();

		/// @brief Initial setup of the camera by default
		void SetupCamera();

		/// @brief Used to update the camera matrixes when moved/each frame
		void UpdateCamera();

		/// @brief Sets the target for the camera to lock on and follow
		/// @param entity Entity for the camera to target
		void SetTarget(std::shared_ptr<Entity> entity);

		/// @brief Set the offset when locking the camera to an entity
		/// @param x Offset in the x axis
		/// @param y Offset in the y axis
		/// @param z Offset in the z axis
		void SetOffset(float x, float y, float z);

		/// @brief Enable the camera following the set target
		void Follow();

		/// @brief Get the view matrix of camera
		/// @return Rend 4x4 view matrix
		rend::mat4 GetView();

		/// @brief Get the projection matrix of camera
		/// @return Rend 4x4 projection matrix
		rend::mat4 GetProj();

	private:
		rend::mat4 viewMatrix;
		rend::mat4 projMatrix;
		rend::vec3 offset = glm::vec3(0);
		rend::vec3 viewDirection;
		std::shared_ptr<Entity> target;
		bool follow;

	};
}