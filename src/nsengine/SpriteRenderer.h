#pragma once
#include <vector> 
#include <rend/rend.h>

#include "Texture.h"
#include "Component.h"
#include "Transform.h"
#include "Entity.h"
#include "Camera.h"

namespace nsengine
{
	struct SpriteRenderer : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick();

		void Animate(std::vector<std::shared_ptr<Texture>>);

	private:
		rend::Mesh mesh;
		rend::Shader shader;
		std::vector<std::shared_ptr<Texture>> animTextures;
		bool animate;
		int currentID;
		float frameTimer = 0;
		int frameCount = 0;
		std::vector<int> ids;
	};

}