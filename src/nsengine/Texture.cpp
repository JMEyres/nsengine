#include "Texture.h"

namespace nsengine
{
	void Texture::onLoad() 
	{
		texture = std::make_shared<rend::Texture>();
		texture->load(getPath().c_str());
		id = texture->id();	
	}
}