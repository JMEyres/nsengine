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
	/// @brief Component to control audio
	struct AudioSource : Component
	{
		void OnTick();

		/// @brief Set the audio source from audio resource
		/// @param _audio Audio resource, contains audio data
		void SetAudio(std::shared_ptr<Audio> _audio);
		/// @brief Play audio source
		void Play();
	protected:
		std::shared_ptr<Audio> audioPtr;
	};
}