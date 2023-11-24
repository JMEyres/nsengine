#pragma once
#include "Resource.h"
#include <stb_image.h>

namespace nsengine
{
	struct Texture : public Resource
	{
		int width, height, channels;
		//void onCreate(int width, int height);
		void onLoad();
	private:
		std::shared_ptr<rend::Texture> texture;
	};
}