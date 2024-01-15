#pragma once
#include <memory>
#include <vector>
#include <type_traits>
#include <iostream>

#include "Component.h"
#include "Core.h"

namespace nsengine
{
	struct Core; // forward declare
	struct Environment;
	struct Component;
	struct Transform;
	struct Camera;

	/// @brief Class containing all the data for the entities
	struct Entity
	{
		/// @brief Adds a component of the given type to the entity and adds it to a list
		/// @tparam T Type of entity to be added
		/// @return Returns the created component
		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->core = GetEnvironment()->GetCore();
			rtn->entity = self;
			rtn->self = rtn;

			components.push_back(rtn);
			rtn->OnCreate();

			return rtn;
		}

		/// @brief Gets a component of a given type on the current entity
		/// @tparam c type of component
		/// @return Component of given type
		template <typename c>
		std::shared_ptr<c> GetComponent()
		{
			for (size_t ci = 0; ci < components.size(); ++ci)
			{
				std::shared_ptr<c> rtn = std::dynamic_pointer_cast<c>(components.at(ci));

				if (rtn) return rtn;
			}
		}

		/// @brief Gets the transform on the current entity
		/// @return Pointer to transform component of entity
		std::shared_ptr<Transform> GetTransform();

		/// @brief Gets the environment entity is a part pf
		/// @return Pointer to the environment
		std::shared_ptr<Environment> GetEnvironment();

	private:
		friend struct Core;
		friend struct Environment;
		
		std::weak_ptr<Environment> environment;
		std::weak_ptr<Entity> self;
		std::weak_ptr<Transform> transform;


		bool alive;
		std::vector<std::shared_ptr<Component> > components; // List of components

		void Initialize();
		void Tick();
		void PhysicsTick();
		void Display();
	};
}