#pragma once
#include "Resource.h"
#include <stb_image.h>

namespace nsengine
{
	/// @brief Texture resource containing data about loaded textures
	struct Texture : public Resource
	{
		//int width, height, channels;
		void OnLoad();

		/// @brief Gets the id of the current texture
		/// @return Integer value of texture id
		int GetID();
	private:
		unsigned int id;
		std::shared_ptr<rend::Texture> texture;
	};
}