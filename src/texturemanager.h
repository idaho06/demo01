#pragma once
#include <SDL2/SDL.h>

enum TextureColor {
    TEXTURE_BLACK,
    TEXTURE_WHITE,
    TEXTURE_TRANS
};


class TextureManager {
    private:
        SDL_Renderer* ren;
        SDL_Texture* tex; 

    public:
        TextureManager(const char* file, SDL_Renderer* ren);
        TextureManager(const SDL_Rect sizerect, TextureColor color, SDL_Renderer* ren);
        ~TextureManager();
        bool Render(const SDL_Rect* srcrect, const SDL_Rect* dstrect);
        SDL_Rect getSizeRect();
};
