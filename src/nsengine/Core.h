#pragma once
#include<SDL2/SDL.h>

#include <memory>;
#include <vector>;
#include <rend/rend.h>

namespace nsengine
{
    struct Environment;
    struct Input;

    struct Core
    {
        static std::shared_ptr<Core> initialize(); // constructs initialize function

        void start();
        void stop();

        std::shared_ptr<Environment> createEnvironment();
        std::shared_ptr<Input> getInput();

    private:
        std::weak_ptr<Core> self;
        bool running;

        std::vector<std::shared_ptr<Environment> > environments;
        std::shared_ptr<Input> input;

        SDL_Window* window;
        SDL_GLContext context;
    };
}