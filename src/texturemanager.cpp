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

bool TextureManager::Render(const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
    SDL_RenderCopy(this->ren, this->tex, srcrect, dstrect);
    return true;
}
    
TextureManager::~TextureManager(){
    SDL_DestroyTexture(this->tex);
}

