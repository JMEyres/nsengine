#include "AudioSource.h"

namespace nsengine
{
	void AudioSource::SetAudio(std::shared_ptr<Audio> audio)
	{
		audioPtr = audio;
		alSourcei(audio->GetSourceID(), AL_BUFFER, audio->GetBufferID());
		
		//alSourcef(sourceId, AL_PITCH, 10);
		//alSourcef(sourceId, AL_GAIN, vol);
	}
	void AudioSource::OnTick()
	{
		glm::vec3 pos = GetEntity()->GetTransform()->GetPosition();
		alSource3f(audioPtr->GetSourceID(), AL_POSITION, pos.x, pos.y, pos.z); // set audio source position
	}

	void AudioSource::Play()
	{
		alSourcePlay(audioPtr->GetSourceID());
	}
}