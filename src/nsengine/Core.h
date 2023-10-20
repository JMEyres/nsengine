#pragma once
#include<SDL2/SDL.h>

#include <memory>;
#include <vector>;

namespace nsengine
{
    struct Entity; // just says it exists - not defined yet

    struct Core
    {
        static std::shared_ptr<Core> initialize(); // constructs initialize function

        void start();
        void stop();

        std::shared_ptr<Entity> addEntity(); // constructs addEntity function
    private:
        std::weak_ptr<Core> self;
        bool running;

        std::vector<std::shared_ptr<Entity> > entities; // List of entities
        SDL_Window* window;
        SDL_GLContext context;
    };
}