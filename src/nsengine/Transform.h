#pragma once
#include "Component.h"
#include <rend/rend.h>

namespace nsengine
{
	/// @brief Component responsible for the entity position/rotation
	struct Transform : public Component
	{
		Transform();

		/// @brief Set the transform to a specific rotation
		/// @param _rotation Vector3 Rotation in xyz axis 
		void SetRotation(rend::vec3 _rotation);

		/// @brief Get the current rotation of transform
		/// @return Vector3 containing rotation in xyz axis
		rend::vec3 GetRotation();

		/// @brief Rotate current transform by a specified amount setup to do one at a time
		/// @param x Rotation in x axis
		/// @param y Rotation in y axis
		/// @param z Rotation in z axis
		void Rotate(float x, float y, float z);

		/// @brief Specifically set the position of the transform
		/// @param _position Vector3 position to set to in xyz axis
		void SetPosition(rend::vec3 _position);

		/// @brief Get the current position of transfrom
		/// @return Vector3 position in xyz axis
		rend::vec3 GetPosition();

		/// @brief Move the Transform current position by specified amount
		/// @param x Movement in x axis
		/// @param y Movement in y axis
		/// @param z Movement in z axis
		void Move(float x, float y, float z);

		/// @brief Set the scale of the transform
		/// @param _scale Vector3 Scale in xyz axis
		void SetScale(rend::vec3 _scale);

		/// @brief Get the current scale of the transform
		/// @return Vector3 scale of transform in xyz axis
		rend::vec3 GetScale();

		/// @brief Compute the model matrix of current transform
		/// @return Model matrix of current transform
		rend::mat4 Model();
	private:
		rend::mat4 mat;
		rend::vec3 rotation;
		rend::vec3 position;
		rend::vec3 scale;
	};
}