#ifndef SDLCONTEXT_H
#define SDLCONTEXT_H

#include <SDL2/SDL.h>
#include <string>
#include <functional>

/**
 * @brief The SDLContext class hides the details of the SDL2 life cycle, and provides the initialization, clean up, and event loop stages.
 */
class SDLContext
{
public:
    bool error;
    std::string errorMessage;

    bool fullscreen;
    int width, height, refreshrate;

    SDL_Window * window;
    SDL_Renderer *renderer;

    public:
        SDLContext(bool fullscreen=false, int width=-1, int height=-1);
        virtual ~SDLContext();

        void showCursor(bool show);
        void cleanUp();

        void loop(int delay, std::function<void(void)> callback);
    protected:
    private:

    void initialize();
    void setError(const char* msg, const char* details = nullptr);
};

#endif // SDLCONTEXT_H
