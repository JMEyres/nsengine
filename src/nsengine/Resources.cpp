#include "Resources.h"
#include "Texture.h"
#include <iostream>

namespace nsengine
{
	std::vector<std::shared_ptr<Texture>> Resources::LoadAnimation(std::string _path, int _frameCount)
	{
		std::vector<std::shared_ptr<Texture>> spriteAnim;
		for (int i = 0; i < _frameCount; ++i)
		{
			std::string newPath = _path + "/_";
			spriteAnim.push_back(Load<Texture>(newPath + std::to_string(i + 1) + ".png"));
		}
		return spriteAnim;
	}
}