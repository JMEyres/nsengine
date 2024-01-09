#include "AudioSource.h"

namespace nsengine
{
	void AudioSource::setAudio(std::shared_ptr<Audio> audio)
	{
		audioPtr = audio;
		alSourcei(audio->getSourceID(), AL_BUFFER, audio->getBufferID());
		
		//alSourcef(sourceId, AL_PITCH, 10);
		//alSourcef(sourceId, AL_GAIN, vol);
	}
	void AudioSource::onTick()
	{
		glm::vec3 pos = getEntity()->getTransform()->getPosition();
		alSource3f(audioPtr->getSourceID(), AL_POSITION, pos.x, pos.y, pos.z);
	}

	void AudioSource::play()
	{
		alSourcePlay(audioPtr->getSourceID());
	}
}