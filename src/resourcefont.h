#ifndef RESOURCEFONTMETRICS_H
#define RESOURCEFONTMETRICS_H

#include <SDL2/SDL.h>
#include <string>

class ResourceFont
{
private:
    int charSeparatorPx, charWidth, charHeight;

public:
    ResourceFont(int charSeparatorPx, int charWidth, int charHeight);

    SDL_Rect getRect(char c);

    void render(SDL_Renderer*renderer, SDL_Texture*pixmap, SDL_Rect destination, const std::string& text);
};

#endif // RESOURCEFONTMETRICS_H
