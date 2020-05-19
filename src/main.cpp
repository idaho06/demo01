#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <iostream>
//#include <stdio.h>
#include "texturemanager.h"

#define HRES 640
#define VRES 480

int main(int argv, char** args)
{

    // Set standard log
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init: Starting engines!!");
    // SDL init all
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* win = SDL_CreateWindow("AkinoDemo01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, HRES*2, VRES*2, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Renderer* ren
        = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    TextureManager * texture = new TextureManager("./akinosoft.bmp", ren);
    //SDL_Rect size;
    //size.w=640;
    //size.h=480;
    //TextureManager * texture = new TextureManager(size,TEXTURE_GREEN, ren);

	// Sound init
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio Error: %s\n", SDL_GetError());
    	return EXIT_FAILURE;
	}
	
	int flags=MIX_INIT_OGG|MIX_INIT_MOD;
	int initted=Mix_Init(flags);
	if((initted&flags) != flags) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init: %s\n", SDL_GetError());
    	return EXIT_FAILURE;
	}
    

	Mix_Music *music;
    music=Mix_LoadMUS("./ARTIST.S3M");
    if(!music) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadMUX: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

	if(Mix_PlayMusic(music, 1)==-1) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Mix_PlayMusic: %s\n", SDL_GetError());
    }

    // hide mouse
    SDL_ShowCursor(SDL_DISABLE);

	// Start the main loop
	bool quit = false;

	SDL_Event e;

	
	while(Mix_PlayingMusic()==1 && !quit ){
		//Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
        }
        SDL_RenderClear(ren);
        texture->Render(nullptr, nullptr);
	    SDL_RenderPresent(ren);
		//SDL_Delay(250);
		//
	}


	// Cleanup
	//
	Mix_FreeMusic(music);
	
	Mix_Quit();
	Mix_CloseAudio();

    //SDL_DestroyTexture(tex);
    delete texture;
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}
