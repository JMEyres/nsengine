#pragma once
#include <memory>;
#include <vector>;
#include <list>

namespace nsengine
{
    struct Entity; // jsut says it exists - not defined yet

    struct Core
    {
        static std::shared_ptr<Core> initialize(); // constructs initialize function
        std::shared_ptr<Entity> addEntity(); // constructs addEntity function

    private:
        std::list<std::shared_ptr<Entity> > entities; // List of entities
    };
}