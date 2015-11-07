#include "resources.h"

#include <iostream>
#include <cstdlib>
#include <SDL2/SDL_image.h>
#include "utils.h"

Resources::Resources(std::shared_ptr<SDLContext> context, const std::string &rootDir)
    : context(context), rootDir(rootDir)
{

}

SDL_Texture *Resources::getFileAsTexture(const std::string &relativePath)
{
    std::string file = Utils::joinPaths(this->rootDir, relativePath);
    auto found = textures.find(file);
    if (found == textures.end()) {
        SDL_Surface *surface = IMG_Load(file.c_str());
        if (surface == 0){
            errorMessage = "Cannot load file " + file;
            return nullptr;
        }
        SDL_Texture *tex = SDL_CreateTextureFromSurface(context->renderer, surface);
        SDL_FreeSurface(surface);

        if (tex == nullptr){
            errorMessage = "Cannot create texture from surface for " + file;
            return nullptr;
        }

        textures.insert(std::pair<std::string, SDL_Texture*>(file, tex));
        return tex;
    }
    return found->second;
}

Resources::~Resources()
{
    for (auto i : textures) {
        SDL_DestroyTexture(i.second);
    }
}

std::string Resources::getErrorMessage()
{
    return errorMessage;
}
