#include "simpleclock.h"

#include <ctime>
#include <sstream>
#include <iomanip>

SimpleClock::SimpleClock(std::shared_ptr<Resources> resources, std::shared_ptr<SDLContext> context)
    : resources(resources), fontMetrics(1, 8, 9), context(context)
{
}

void SimpleClock::render()
{
    SDL_Texture* fontPixmap = resources->getFileAsTexture("res/Victoria.png");

    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::stringstream buf;
    buf << std::setw(2) << std::setfill('0') << ltm->tm_hour;
    buf << " ";
    buf << std::setw(2) << std::setfill('0') << ltm->tm_min ;

    std::string hm = buf.str();
    int charWidth = 80;
    int txtWidth = hm.size() * charWidth;

    SDL_Rect dest;
    dest.x = context->width/2 - (txtWidth/2);
    dest.y = 20;
    dest.w = charWidth;
    dest.h = charWidth + (charWidth/3);
    fontMetrics.render(context->renderer, fontPixmap, dest, hm);

    buf.str("");
    buf << std::setw(2) << std::setfill('0') << ltm->tm_sec;

    int secCharWidth = 40;
    std::string sec = buf.str();
    int secWidth = sec.size()*secCharWidth;
    dest.h = secCharWidth + secCharWidth/3;
    dest.y = context->height - dest.h - 25;
    dest.x = context->width - secWidth - 1;
    dest.w = secCharWidth;
    fontMetrics.render(context->renderer, fontPixmap, dest, sec);

}

