#pragma once
#include<SDL2/SDL.h>

#include <memory>;
#include <vector>;
#include <rend/rend.h>
#include <algorithm>
#include <stdexcept>

#include "Environment.h"
#include "Entity.h"
#include "Transform.h"
#include "Input.h"
#include "pellet/btBulletDynamicsCommon.h"


namespace nsengine
{
    struct Environment;
    struct Input;
    struct Resources;

    struct Core
    {
        static std::shared_ptr<Core> initialize(); // constructs initialize function

        void start();
        void stop();

        std::shared_ptr<Environment> createEnvironment();
        std::shared_ptr<Input> getInput();
        std::shared_ptr<Resources> getResources();

        template <typename T>
        void Find(std::vector<std::shared_ptr<T> >& out)
        {
            for (size_t i = 0; i < environments.size(); ++i)
            {
                std::shared_ptr<Environment> env = environments.at(i);
                for (size_t ei = 0; ei < env->entities.size(); ++ei)
                {
                    std::shared_ptr<Entity> ent = env->entities.at(ei);

                    for (size_t ci = 0; ci < ent->components.size(); ++ci)
                    {
                        std::shared_ptr<Component> com = ent->components.at(ci);

                        std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(com);

                        if (t)
                            out.push_back(t);
                    }
                }
            }
        }
        
        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);
        btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
        btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
        btAlignedObjectArray <btCollisionShape*> collisionShapes;

    private:
        std::weak_ptr<Core> self;
        bool running;

        std::vector<std::shared_ptr<Environment> > environments;
        std::shared_ptr<Resources> resources;
        std::shared_ptr<Input> input;

        SDL_Window* window;
        SDL_GLContext context;
    };
}