#include <SDL2/SDL.h>
#include "texturemanager.h"

TextureManager::TextureManager(const char* file, SDL_Renderer* ren){
    this->tex = nullptr;
    this->ren = ren;
    SDL_Surface* bmp = SDL_LoadBMP(file);
    if (bmp == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        //TODO: Throw exception
    }

    this->tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (this->tex == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        //TODO: Throw exception
    }
  
}

TextureManager::TextureManager(const SDL_Rect sizerect, TextureColor color, SDL_Renderer* ren){
    this->tex = nullptr;
    this->ren = ren;
    SDL_Surface* surface = nullptr;
    surface = SDL_CreateRGBSurfaceWithFormat(0, sizerect.w, sizerect.h, 32, SDL_PIXELFORMAT_RGBA32);
    if (surface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRGBSurface() failed: %s\n", SDL_GetError());
        //TODO: Throw exception
    }
    //TODO: Fill with color
    this->tex = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    if (this->tex == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        //TODO: Throw exception
    }
}

bool TextureManager::Render(const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
    SDL_RenderCopy(this->ren, this->tex, srcrect, dstrect);
    return true;
}

SDL_Rect TextureManager::getSizeRect(){
    SDL_Rect size;
    size.x=0;
    size.y=0;
    if (this->tex == nullptr) {
        size.w=0;
        size.h=0;
    } else {
        int w, h;
        SDL_QueryTexture(this->tex, NULL, NULL, &w, &h);
        size.w=w;
        size.h=h;
    }
    return size;
}


TextureManager::~TextureManager(){
    SDL_DestroyTexture(this->tex);
}
