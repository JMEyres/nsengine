#pragma once

#include "Component.h"
#include "Entity.h"
#include "Audio.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <rend/rend.h>
#include <string>
#include <vector>
#include <stdexcept>


namespace nsengine
{
	struct AudioSource : Component
	{
		void onTick();

		void setAudio(std::shared_ptr<Audio> audio);
		void play();
	protected:
		std::shared_ptr<Audio> audioPtr;
	};
}