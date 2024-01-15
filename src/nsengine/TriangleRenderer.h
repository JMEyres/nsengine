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
	/// @brief Component to simply render a triangle to screen
	struct TriangleRenderer : Component
	{
	private:
		rend::Mesh mesh;
		rend::Shader shader;

		void OnInitialize();
		void OnDisplay();
		int id;
	};
}