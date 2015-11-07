#include "resourcefont.h"

ResourceFont::ResourceFont(int charSeparatorPx, int charWidth, int charHeight)
    : charSeparatorPx(charSeparatorPx), charWidth(charWidth), charHeight(charHeight)
{

}

SDL_Rect ResourceFont::getRect(char c)
{
    int offset = c - '!';
    if (offset < 0) {
        offset = 0;
    }
    SDL_Rect rect;
    rect.x = charSeparatorPx + (offset * (charWidth+charSeparatorPx));
    rect.y = 0;
    rect.w = charWidth;
    rect.h = charHeight;
    return rect;
}

void ResourceFont::render(SDL_Renderer *renderer, SDL_Texture *pixmap, SDL_Rect destination, const std::string &text)
{
    for(auto c = text.begin(); c != text.end(); c++) {
        auto src = getRect(*c);
        if (*c>32) {
            SDL_RenderCopy(renderer, pixmap, &src, &destination);
        }
        destination.x += destination.w;
    }
}
