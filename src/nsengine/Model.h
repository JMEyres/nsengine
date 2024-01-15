#pragma once
#include "Resource.h"

namespace nsengine
{
	/// @brief Model resource for loading models to displayed in game
	struct Model : Resource
	{
		void OnLoad();

		/// @brief Gets the model loaded
		/// @return Pointer to loaded model
		std::shared_ptr<rend::Model> GetModel();
	private:
		std::shared_ptr<rend::Model> model;
	};
}