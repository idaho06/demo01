#pragma once
#include <SDL2/SDL.h>


class TextureManager {
    private:
        SDL_Renderer* ren;
        SDL_Texture* tex; 

    public:
        TextureManager(const char* file, SDL_Renderer* ren);
        ~TextureManager();
        bool Render(const SDL_Rect* srcrect, const SDL_Rect* dstrect);
};
