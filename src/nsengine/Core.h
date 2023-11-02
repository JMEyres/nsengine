#pragma once
#include<SDL2/SDL.h>

#include <memory>;
#include <vector>;
#include <rend/rend.h>

namespace nsengine
{
    struct Entity; // just says it exists - not defined yet

    struct Core
    {
        static std::shared_ptr<Core> initialize(); // constructs initialize function

        void start();
        void stop();

        std::shared_ptr<Entity> addEntity(); // constructs addEntity function
        rend::vec3 pos;
    private:
        std::weak_ptr<Core> self;
        bool running;

        rend::vec3 test();

        std::vector<std::shared_ptr<Entity> > entities; // List of entities
        SDL_Window* window;
        SDL_GLContext context;
    };
}