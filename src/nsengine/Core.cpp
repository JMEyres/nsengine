#include "Core.h"
#include "Entity.h"

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

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}
		for (size_t ei = 0; ei < entities.size(); ++ei)
		{
			entities.at(ei)->tick();
		}

		

		rend::Model model("data/models/curuthers/curuthers.obj");
		rend::ModelShader modelShader;

		modelShader.projection(rend::perspective(
			rend::radians(45.0f), 1.0f, 0.1f, 100.0f
		));

		modelShader.model(rend::translate(rend::mat4(1.0f), rend::vec3(0, 0, -10)));

		modelShader.model(model);
		modelShader.render();

		for (size_t ei = 0; ei < entities.size(); ++ei)
		{
			entities.at(ei)->display();
		}

		SDL_Rend_SwapWindow(window);
	}
}

void Core::stop()
{
	running = false;
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

	rtn->core = self; // allows entity to point upwards
	rtn->self = rtn; // will allow component to point upwards

	entities.push_back(rtn);

	return rtn;
}

}