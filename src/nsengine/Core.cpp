#include "Core.h"
#include "Resources.h"

namespace nsengine
{
	std::shared_ptr<Core> Core::Initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>(); // make_shared = new

		rtn->physicsWorld = rtn->physicsCommon.createPhysicsWorld();

		rtn->self = rtn;
		rtn->running = false;
		rtn->input = std::make_shared<Input>();
		rtn->resources = std::make_shared<Resources>();

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::runtime_error("Failed to initialize SDL");
		}

		rtn->window = SDL_CreateWindow("SDL Window",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			1152, 864, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		if (!rtn->window)
		{
			throw std::runtime_error("Failed to create window");
		}

		rtn->context = SDL_Rend_CreateContext(rtn->window);

		if (!rtn->context)
		{
			throw std::runtime_error("Failed to create context");
		}

		// Audio

		rtn->audioDevice = alcOpenDevice(NULL);

		if (!rtn->audioDevice)
		{
			throw std::runtime_error("Failed to open audio device");
		}

		rtn->audioContext = alcCreateContext(rtn->audioDevice, NULL);

		if (!rtn->audioContext)
		{
			alcCloseDevice(rtn->audioDevice);
			throw std::runtime_error("Failed to create audio context");
		}

		if (!alcMakeContextCurrent(rtn->audioContext))
		{
			alcDestroyContext(rtn->audioContext);
			alcCloseDevice(rtn->audioDevice);
			throw std::runtime_error("Failed to make context current");
		}

		return rtn;
	}

	void Core::Start()
	{
		running = true;
		SDL_Event event = { 0 };
		physicsWorld->setGravity(rp3d::Vector3(0, -2, 0));

		SDL_SetRelativeMouseMode(SDL_TRUE);

		for (size_t i = 0; i < environments.size(); ++i)
		{
			for (size_t ei = 0; ei < environments.at(i)->entities.size(); ++ei)
			{
				environments.at(i)->entities.at(ei)->Initialize();
			}
		}

		while (running)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						running = false;
						break;
					case SDL_KEYDOWN:
						if (std::find(input->keys.begin(), input->keys.end(), event.key.keysym.sym) == input->keys.end()) input->keys.push_back(event.key.keysym.sym);
						input->pressedKeys.push_back(event.key.keysym.sym);
						break;
					case SDL_KEYUP:
						for (size_t ki = 0; ki < input->keys.size(); ++ki)
						{
							if (input->keys.at(ki) == event.key.keysym.sym)
							{
								input->keys.erase(input->keys.begin() + ki);
							}
						}

						input->releasedKeys.push_back(event.key.keysym.sym);
						break;
				}
			}

			SDL_GetRelativeMouseState(&input->mouseX, &input->mouseY);
			float timeStep = 1.0f / 60.0f;

			for (size_t i = 0; i < environments.size(); ++i)
			{
				for (size_t ei = 0; ei < environments.at(i)->entities.size(); ++ei)
				{
					for (int t = 0; t < 1; t++) {

						physicsWorld->update(timeStep);
						environments.at(i)->entities.at(ei)->PhysicsTick();
					}
				}
			}

			for (size_t i = 0; i < environments.size(); ++i)
			{
				for (size_t ei = 0; ei < environments.at(i)->entities.size(); ++ei)
				{
					environments.at(i)->entities.at(ei)->Tick();
				}
			}
			float time = SDL_GetTicks();
			float diff = time - lastTime;
			deltaTime = diff / 1000.0f;
			lastTime = time;
			SDL_Rend_ClearWindow(window);

			for (size_t i = 0; i < environments.size(); ++i)
			{
				for (size_t ei = 0; ei < environments.at(i)->entities.size(); ++ei)
				{
					environments.at(i)->entities.at(ei)->Display();
				}
			}
			input->ClearInput();
			SDL_Rend_SwapWindow(window);
		}
	}

	void Core::Stop()
	{
		running = false;
		alcMakeContextCurrent(NULL);
		alcDestroyContext(audioContext);
		alcCloseDevice(audioDevice);
	}

	std::shared_ptr<Environment> Core::CreateEnvironment()
	{
		std::shared_ptr<Environment> rtn = std::make_shared<Environment>();

		rtn->core = self; // allows environment to point upwards
		rtn->self = rtn; // will allow entity to point upwards

		environments.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Input> Core::GetInput()
	{
		return input;
	}

	std::shared_ptr<Resources> Core::GetResources()
	{
		return resources;
	}

	float Core::GetDeltaTime()
	{
		return deltaTime;
	}
}