#pragma once
#include "Component.h"

#include <rend/rend.h>
#include <string>

namespace nsengine
{
	struct Model;
	struct Texture;
	struct Camera;

	/// @brief Component responsible for rendering models
	struct Renderer : Component
	{
		/// @brief Set the path to model to be rendered
		/// @param _path String path to modee
		void SetPath(std::string _path);
	private:
		void OnDisplay();
		void OnInitialize();

		std::string path;
		std::shared_ptr<rend::Model> model;
		rend::ModelShader modelShader;
		bool disable = false;
	};
}