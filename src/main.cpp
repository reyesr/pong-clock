#include <cstdlib>
#include <memory>
#include <SDL2/SDL.h>
#include <iostream>
#include "sdlcontext.h"
#include "resources.h"
#include "resourcefont.h"
#include "utils.h"

#include "simpleclock.h"
#include "ponggame.h"

int main (int, char** argv )
{
    // Creating and initializing the SDL context
    std::shared_ptr<SDLContext> context(new SDLContext(false, 480, 320));
    if (context->error) {
        std::cout << context->errorMessage << std::endl;
        return 1;
    }

    // the Resource class needs the know the location of the executable
    // in order to retrieve the resources (in case the currentdir is not
    // the executable dir)
    std::string rootDir = Utils::basedir(argv[0]);
    std::shared_ptr<Resources> resources(new Resources(context, rootDir));

    context->showCursor(false);

    SimpleClock sclock(resources, context); // responsible for displaying the time of day
    PongGame pong(context);   // manages the pong game
    Graphics g(context);
    Color BLACK(0,0,0);

    context->loop(50, [&]() -> void {
        g.setColor(BLACK).clear();
        pong.render();
        sclock.render();
    });

    context->cleanUp();
    return 0;
}
