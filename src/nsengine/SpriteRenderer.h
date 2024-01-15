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
	/// @brief Component responsible for rendering sprites
	struct SpriteRenderer : Component
	{
		void OnInitialize();
		void OnDisplay();
		void OnTick();

		/// @brief Animates the sprite with given frames
		/// @param _animFrames Frames of the animation
		void Animate(std::vector<std::shared_ptr<Texture>> _animFrames);

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