#include "Texture.h"
#include <filesystem>
#include <iostream>

namespace nsengine
{
	void Texture::OnLoad() // Set variables up when loaded
	{
		texture = std::make_shared<rend::Texture>();
		texture->load(GetPath().c_str());
		id = texture->id();
	}

	int Texture::GetID()
	{
		return id;
	}
}