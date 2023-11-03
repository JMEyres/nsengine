#pragma once
#include<SDL2/SDL.h>

#include <memory>;
#include <vector>;
#include <rend/rend.h>

namespace nsengine
{
    struct Environment;

    struct Core
    {
        static std::shared_ptr<Core> initialize(); // constructs initialize function

        void start();
        void stop();

        std::shared_ptr<Environment> createEnvironment();

    private:
        std::weak_ptr<Core> self;
        bool running;

        std::vector<std::shared_ptr<Environment> > environments;

        SDL_Window* window;
        SDL_GLContext context;
    };
}