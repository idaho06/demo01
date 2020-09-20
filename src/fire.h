#pragma once
#include <SDL2/SDL.h>
#include "effect.h"
#include "texturemanager.h"



class Fire: public Effect {
    private:
        SDL_Surface * sur;
        SDL_Rect srcrect;
        SDL_Rect dstrect;
    protected:
    public:
        Fire(SDL_Rect size, int speed);
        ~Fire();
        bool Apply(TextureManager * texture);
};
