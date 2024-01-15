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
	/// @brief Audio resource hold information on audio clips
	struct Audio : Resource
	{
		void OnLoad();
		/// @brief Loads ogg file from specified path
		/// @param _path String path to source audio file
		/// @param _buffer Raw audio data
		/// @param _format Format of audio data
		/// @param _freq Frequence of audio data
		void LoadOgg(const std::string& _path, std::vector<unsigned char>& _buffer, ALenum& _format, ALsizei& _freq);
		/// @brief Gets the source id of audio resource
		/// @return integer audio source id
		ALuint GetSourceID() { return sourceId; };
		/// @brief Gets the buffer id of audio resource
		/// @return integer buffer audio source id
		ALuint GetBufferID() { return bufferId; };
	private:
		std::shared_ptr<Audio> audio;
	protected:
		ALuint sourceId = 0;
		ALuint bufferId = 0;
	};
}