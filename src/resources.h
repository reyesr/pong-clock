#ifndef RESOURCES_H
#define RESOURCES_H

#include "sdlcontext.h"
#include <SDL2/SDL.h>
#include <memory>
#include <map>

class Resources
{
private:
    std::shared_ptr<SDLContext> context;
    std::map<std::string, SDL_Texture*> textures;
    std::string errorMessage;
    std::string rootDir;

public:
    Resources(std::shared_ptr<SDLContext> context, const std::string& rootDir);
    SDL_Texture* getFileAsTexture(const std::string& relativePath);

    virtual ~Resources();
    std::string getErrorMessage();
protected:
private:
};

#endif // RESOURCES_H
