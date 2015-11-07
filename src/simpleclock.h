#ifndef SIMPLECLOCK_H
#define SIMPLECLOCK_H

#include <memory>
#include "sdlcontext.h"
#include "resources.h"
#include "resourcefont.h"

class SimpleClock
{
private:
    std::shared_ptr<Resources> resources;
    ResourceFont fontMetrics;
    std::shared_ptr<SDLContext> context;

public:
    SimpleClock(std::shared_ptr<Resources> resources, std::shared_ptr<SDLContext> context);
    void render();
};

#endif // SIMPLECLOCK_H
