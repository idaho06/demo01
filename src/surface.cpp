//#include <vector>
//#include <algorithm>
#include "surface.h"
#include "texturemanager.h"
#include <SDL2/SDL.h>

Surface::Surface(const char* file){
    this->sur = nullptr;
    this->srcrect = nullptr;
    this->dstrect = nullptr;

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "We are going to load: %s\n", file);
    SDL_Surface* bmp = SDL_LoadBMP(file);
    if (bmp == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        //TODO: Throw exception
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Creating surface. \n");
    this->sur = SDL_ConvertSurfaceFormat(bmp, SDL_PIXELFORMAT_ARGB8888, 0);
    if (this->sur == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_ConvertSurfaceFormat Error: %s\n", SDL_GetError());
        //TODO: Throw exception
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing bmp. \n");
    SDL_FreeSurface(bmp);

    // Let's set the srcrect
    SDL_GetClipRect(this->sur, this->srcrect);
}

Surface::~Surface(){
    if (this->sur != nullptr) {
        SDL_FreeSurface(this->sur);
    }
        
}


bool Surface::Apply(TextureManager * texture){
    tick++;
    SDL_Surface * destsur = texture->getSurface();
    SDL_Surface * srcsur = this->sur;

    if (SDL_BlitSurface(srcsur, this->srcrect, destsur, this->dstrect) < 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_BlitSurface Error: %s\n", SDL_GetError());
        return false;
    }


    return true;
}
