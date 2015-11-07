#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <memory>
#include "sdlcontext.h"

struct Color {
    Uint8 r,g,b,a;
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a=1);
};

class Graphics
{
    std::shared_ptr<SDLContext> context;

public:
    Graphics(std::shared_ptr<SDLContext> context);

    Graphics& clear();
    Graphics& present();
    Graphics& setColor(const Color& color);

    Graphics& fillRect(int x, int y, int width, int height);

    int width() const;
    int height() const;
};

#endif // GRAPHICS_H
