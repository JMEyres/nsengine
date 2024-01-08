#pragma once
#include "Component.h"

#include <rend/rend.h>
#include <string>

namespace nsengine
{
	struct Model;
	struct Texture;
	struct Camera;
	struct Renderer : Component
	{
		std::string path;

	private:

		std::shared_ptr<rend::Model> model;
		rend::ModelShader modelShader;
		void onInitialize();
		void onDisplay();
	};
}