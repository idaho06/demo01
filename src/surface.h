#pragma once
//#include <vector>
#include "effect.h"
#include "texturemanager.h"
#include <SDL2/SDL.h>

class Surface: public Effect {
    private:
        SDL_Surface * sur;
        SDL_Rect * srcrect;
        SDL_Rect * dstrect;
    protected:
    public:
        Surface(const char* file);
        ~Surface();
        bool Apply(TextureManager * texture);
};
