#include "sdlcontext.h"

SDLContext::SDLContext(bool fullscreen, int width, int height)
    : error(false), errorMessage(""), fullscreen(fullscreen), width(width), height(height), refreshrate(-1),
        window(nullptr), renderer(nullptr)
{
    initialize();
}

SDLContext::~SDLContext()
{
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
}

void SDLContext::initialize() {
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        setError("SDL Init error: ", SDL_GetError());
        return;
    }

    SDL_DisplayMode current;
    if (SDL_GetCurrentDisplayMode(0, &current) != 0) {

        setError("SDL_GetCurrentDisplayMode: ", SDL_GetError());
    }

    this->width = this->width == -1 ? current.w : this->width;
    this->height = this->height == -1 ? current.h : this->height;
    this->refreshrate = current.refresh_rate;
    if (this->width == current.w && this->height == current.h) {
        fullscreen = true; // forced
    }

    int flags = SDL_WINDOW_OPENGL;
    if (this->fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN|SDL_WINDOW_BORDERLESS;
    }
    this->window = SDL_CreateWindow(
        "Pong clock",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        this->width,                               // width, in pixels
        this->height,                               // height, in pixels
        flags // flags - see below
    );

    if (window == nullptr) {
        // In the case that the window could not be made...
        setError("Could not create window: ", SDL_GetError());
        return;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if (renderer == nullptr){
        setError("SDL_CreateRenderer Error:", SDL_GetError());
        return;
    }

}

void SDLContext::setError(const char* msg, const char* details) {
    this->error = true;
    this->errorMessage = msg;
    if (details != nullptr) {
        this->errorMessage += details;
    }
}

void SDLContext::showCursor(bool show)
{
    SDL_ShowCursor(show?1:0);
}

void SDLContext::cleanUp()
{
    SDL_Quit();
}

void SDLContext::loop(int delay, std::function<void ()> callback)
{
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
        callback();

        SDL_RenderPresent(renderer);
        SDL_Delay(delay);
    }
}
