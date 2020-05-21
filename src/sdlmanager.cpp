#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "sdlmanager.h"

#define HRES 640
#define VRES 480


SDLManager::SDLManager(){
    this->ren = nullptr;
    this->win = nullptr;
    this->music = nullptr;

    // Set standard log
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init: Starting engines!!");
    // SDL init all
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n", SDL_GetError());
        //return EXIT_FAILURE;
        //TODO: Throw exception
        exit(EXIT_FAILURE);
    }

    // Starts window
    this->win 
        = SDL_CreateWindow("AkinoDemo01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, HRES*2, VRES*2, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        //return EXIT_FAILURE;
        //TODO: Throw exception
        exit(EXIT_FAILURE);
    }
    // Starts renderer
    this->ren
        = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        // TODO: Throw exception
        exit(EXIT_FAILURE);
    }

    // hide mouse
    SDL_ShowCursor(SDL_DISABLE);

    // Audio init
   	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio Error: %s\n", SDL_GetError());
        // TODO: Trow exception
        exit(EXIT_FAILURE);
	}
	
	int flags=MIX_INIT_OGG|MIX_INIT_MOD;
	int initted = Mix_Init(flags);
	if((initted&flags) != flags) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init: %s\n", SDL_GetError());
    	//TODO: Throw exception
        exit(EXIT_FAILURE);
	}
 
}

bool SDLManager::loadPlayMusic(const char * file){
    this->music = Mix_LoadMUS(file);
    if(!this->music) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadMUX: %s\n", SDL_GetError());
        //return EXIT_FAILURE;
    }

	if(Mix_PlayMusic(music, 1) == -1) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Mix_PlayMusic: %s\n", SDL_GetError());
    }
    return true;
}
   

void SDLManager::stopMusic(){
    Mix_HaltMusic();
}

SDL_Renderer * SDLManager::getRenderer(){
    return this->ren;
}

SDLManager::~SDLManager(){
    // Cleanup

    // Stop music and clean music memory
    Mix_FreeMusic(this->music);

    // Stop mixer engine
    Mix_Quit();
    Mix_CloseAudio();

    // destroy renderer and wndow
    SDL_DestroyRenderer(this->ren);
    SDL_DestroyWindow(this->win);
    SDL_Quit();

}
