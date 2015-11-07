#include "graphics.h"

Graphics::Graphics(std::shared_ptr<SDLContext> context)
    : context(context)
{

}

Graphics& Graphics::clear()
{
    SDL_RenderClear(context->renderer);
    return *this;
}

Graphics &Graphics::present()
{
    SDL_RenderPresent(context->renderer);
    return *this;
}

Graphics &Graphics::setColor(const Color &color)
{
    SDL_SetRenderDrawColor(context->renderer, color.r, color.g, color.b, 1 /*currentColor.a*/);
    return *this;
}


Graphics &Graphics::fillRect(int x1, int y1, int width, int height)
{
    SDL_Rect rect;
    rect.x = x1;
    rect.y = y1;
    rect.w = width;
    rect.h = height;


    Color col(177,177,177);
    setColor(col);
    SDL_RenderFillRect(context->renderer, &rect);
    return *this;
}

int Graphics::width() const
{
    return context->width;
}

int Graphics::height() const
{
    return context->height;
}


Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : r(r), g(g), b(b), a(a)
{
}

