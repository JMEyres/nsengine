#include "Texture.h"

namespace nsengine
{
	void Texture::onLoad() 
	{
		texture = std::make_shared<rend::Texture>();
		texture->load(getPath().c_str());
		//test.;

			//texture.load(stbi_load((getPath()+".png").c_str(), &width, &height, &channels, STBI_rgb_alpha));
		//getPath();
		
	}
}