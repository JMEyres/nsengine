#include "Core.h"
#include "Environment.h"
#include "Entity.h"
#include "Transform.h"

#include <rend/rend.h>

#include <stdexcept>

namespace nsengine
{
std::shared_ptr<Core> Core::initialize()
{
	std::shared_ptr<Core> rtn = std::make_shared<Core>(); // make_shared = new

	rtn->self = rtn;
	rtn->running = false;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error("Failed to initialize SDL");
	}

	rtn->window = SDL_CreateWindow("SDL Window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!rtn->window)
	{
		throw std::runtime_error("Failed to create window");
	}

	rtn->context = SDL_Rend_CreateContext(rtn->window);

	if (!rtn->context)
	{
		throw std::runtime_error("Failed to create context");
	}

	return rtn;
}

void Core::start()
{
	running = true;
	SDL_Event event = { 0 };

	for(size_t i = 0; i < environments.size(); ++i)
	{
		for (size_t ei = 0; ei < environments.at(i)->entities.size(); ++ei)
		{
			environments.at(i)->entities.at(ei)->initialize();
		}
	}

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}

		for (size_t i = 0; i < environments.size(); ++i)
		{
			for (size_t ei = 0; ei < environments.at(i)->entities.size(); ++ei)
			{
				environments.at(i)->entities.at(ei)->tick();
			}
		}
		SDL_Rend_ClearWindow(window);

		for (size_t i = 0; i < environments.size(); ++i)
		{
			for (size_t ei = 0; ei < environments.at(i)->entities.size(); ++ei)
			{
				environments.at(i)->entities.at(ei)->display();
			}
		}

		SDL_Rend_SwapWindow(window);
	}
}

void Core::stop()
{
	running = false;
}

std::shared_ptr<Environment> Core::createEnvironment()
{
	std::shared_ptr<Environment> rtn = std::make_shared<Environment>();

	rtn->core = self; // allows environment to point upwards
	rtn->self = rtn; // will allow entity to point upwards

	environments.push_back(rtn);

	return rtn;
}

}