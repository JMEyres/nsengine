#pragma once
#include "Component.h"
#include <iostream>
#include <rend/rend.h>
#include "Transform.h"
#include "Entity.h"

namespace nsengine
{
	struct Texture;
	struct Camera;
	struct TriangleRenderer : Component
	{
	private:
		rend::Mesh mesh;
		rend::Shader shader;

		void onInitialize();
		void onDisplay();
		int id;
	};
}