#pragma once
#include "Component.h"

#include <rend/rend.h>

namespace nsengine
{
	struct Model;
	struct Texture;
	struct Renderer : Component
	{
	private:
		rend::Model model;
		rend::ModelShader modelShader;
		void onInitialize();
		void onDisplay();
	};
}