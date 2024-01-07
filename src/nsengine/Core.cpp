#include "Core.h"
#include "Resources.h"


namespace nsengine
{
std::shared_ptr<Core> Core::initialize()
{
	std::shared_ptr<Core> rtn = std::make_shared<Core>(); // make_shared = new

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

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));

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

			else if (event.type == SDL_KEYDOWN)
			{
				if(std::find(input->keys.begin(), input->keys.end(), event.key.keysym.sym) == input->keys.end()) input->keys.push_back(event.key.keysym.sym);
				input->pressedKeys.push_back(event.key.keysym.sym);
			}

			else if (event.type == SDL_KEYUP)
			{
				for (size_t ki = 0; ki < input->keys.size(); ++ki)
				{
					if (input->keys.at(ki) == event.key.keysym.sym)
					{
						input->keys.erase(input->keys.begin() + ki);
					}
				}

				input->releasedKeys.push_back(event.key.keysym.sym);
			}

			switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE: running = false; break;
			}
		}

		//input->isKeyHeld('a');
		//input->isKeyPressed('d');
		//input->isKeyReleased(SDLK_LSHIFT);

		for (int i = 0; i < 60; ++i)
		{
			dynamicsWorld->stepSimulation(1.f / 60.f, 10);
			//for (int j = 0; j < dynamicsWorld->getNumCollisionObjects(); ++j) // collision objects = rigidbody
			//{
			//	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			//	btRigidBody* body = btRigidBody::upcast(obj);
			//	btTransform trans;
			//	if (body && body->getMotionState())
			//	{
			//		body->getMotionState()->getWorldTransform(trans);
			//	}
			//	else
			//	{
			//		trans = obj->getWorldTransform();
			//	}
			//	printf("world pos object % d = % f, % f, % f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
			//}
			for (size_t i = 0; i < environments.size(); ++i)
			{
				for (size_t ei = 0; ei < environments.at(i)->entities.size(); ++ei)
				{
					environments.at(i)->entities.at(ei)->physicsTick();
				}
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
		input->clearInput();
		SDL_Rend_SwapWindow(window);
	}

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;
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

std::shared_ptr<Input> Core::getInput()
{
	return input;
}

std::shared_ptr<Resources> Core::getResources()
{
	return resources;
}
}