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
#include <reactphysics3d/reactphysics3d.h>
#include <AL/al.h>
#include <AL/alc.h>


namespace nsengine
{
    struct Environment;
    struct Input;
    struct Resources;

    /// @brief Main manager for the rest of the engine
    struct Core
    {
        /// @brief Initializes the core manager
        /// @return Pointer to core
        static std::shared_ptr<Core> Initialize();

        /// @brief Start the program
        void Start();

        /// @brief Stop the program
        void Stop();

        /// @brief Create an environment
        /// @return Pointer to that environment
        std::shared_ptr<Environment> CreateEnvironment();

        /// @brief Gets the input manager
        /// @return Pointer to the input for use elsewhere
        std::shared_ptr<Input> GetInput();

        /// @brief Get the resource manager
        /// @return Pointer to the resource manager
        std::shared_ptr<Resources> GetResources();

        /// @brief Works out delta time
        /// @return Delta time in float format
        float GetDeltaTime();

        /// @brief Finds a list of all components of a specific type
        /// @tparam T Type to find
        /// @param out List of components
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

        rp3d::PhysicsCommon physicsCommon;
        rp3d::PhysicsWorld* physicsWorld;

    private:
        std::weak_ptr<Core> self;
        bool running;

        std::vector<std::shared_ptr<Environment> > environments;
        std::shared_ptr<Resources> resources;
        std::shared_ptr<Input> input;

        SDL_Window* window;
        SDL_GLContext context;

        ALCdevice* audioDevice;
        ALCcontext* audioContext;

        float lastTime = SDL_GetTicks();
        float deltaTime;
    };
}