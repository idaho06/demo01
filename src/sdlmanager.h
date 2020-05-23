#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class SDLManager {
    private:
        SDL_Renderer* ren;
        SDL_Window* win;
        Mix_Music *music;  
    public:
        SDLManager();
        ~SDLManager();
        SDL_Renderer * getRenderer();
        bool loadPlayMusic(const char * file);
        void stopMusic();

};
