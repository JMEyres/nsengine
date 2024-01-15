#pragma once
#include<memory>
#include<vector>
#include <iostream>

#include "Entity.h"
#include "Transform.h"

namespace nsengine
{
	struct Entity; // just says it exists - not defined yet
	struct Core;
	struct Camera;

	/// @brief Class containing data about the environment or 'world'
	struct Environment
	{
		/// @brief Adds an entity to the environment and pushes it back to an internal list 
		/// @return Pointer to that entity
		std::shared_ptr<Entity> AddEntity();

		/// @brief Adds a camera to the environments internal list, so this camera can be grabbed and referenced elsewhere
		/// @param cam Camera to add to the list
		void AddCamera(std::shared_ptr<Camera> cam);

		/// @brief Gets the core object
		/// @return Pointer to core
		std::shared_ptr<Core> GetCore();

		/// @brief Get a specific camera by id
		/// @param camIndex ID of camera to return
		/// @return Pointer to selected camera
		std::shared_ptr<Camera> GetCamera(int camIndex);

	private:
		friend struct Core;

		std::weak_ptr<Core> core; // core owns environments
		std::weak_ptr<Environment> self;

		std::vector<std::shared_ptr<Entity> > entities; // List of entities
		std::vector<std::shared_ptr<Camera> > cameras; // List of entities
	};
}