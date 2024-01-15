#pragma once
#include <memory>

namespace nsengine
{
	struct Entity; // forward declare entity
	struct Core;

	/// @brief Base class for all ECS components to inherit from
	struct Component
	{
	public:
		/// @brief Runs before the game loop starts, used to setup anything needing to be done once beforehand
		virtual void OnInitialize();
		/// @brief Runs every single frame, used to update in realtime
		virtual void OnTick();
		/// @brief Runs every frame before on tick used to handle physics, ticks during physics step
		virtual void OnPhysicsTick();
		/// @brief Runs when component is initially created
		virtual void OnCreate();
		/// @brief Last function to run, used for displaying to screen i.e. rendering
		virtual void OnDisplay();

		/// @brief Gets the current entity
		/// @return The parent entity
		std::shared_ptr<Entity> GetEntity();
		/// @brief Shortcut to get core
		/// @return shared_ptr to core
		std::shared_ptr<Core> GetCore();

		std::weak_ptr<Core> core;
	private:
		friend struct Entity;

		std::weak_ptr<Entity> entity; // entity owns component object

		void Initialize();
		void Tick();
		void PhysicsTick();
		void Create();
		void Display();
	protected:
		std::weak_ptr<Component> self; // entity owns component object
	};
}