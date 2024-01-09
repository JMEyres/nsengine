#pragma once
#include "Resource.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <rend/rend.h>
#include <string>
#include <vector>
#include <stdexcept>

namespace nsengine
{
	struct Audio : Resource
	{
		void onLoad();
		void load_ogg(const std::string&, std::vector<unsigned char>&, ALenum&, ALsizei&);
		ALuint getSourceID() { return sourceId; };
		ALuint getBufferID() { return bufferId; };
	private:
		std::shared_ptr<Audio> audio;
	protected:
		ALuint sourceId = 0;
		ALuint bufferId = 0;
	};
}