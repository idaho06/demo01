#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <iostream>
//#include <stdio.h>

int main(int argv, char** args)
{

    // Set standard log
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init: Init all");
	//printf("%s \n", "Init all");
    // SDL init all
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* win = SDL_CreateWindow("Akino test!", 100, 100, 620, 387, SDL_WINDOW_SHOWN);
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

    SDL_Surface* bmp = SDL_LoadBMP("./akinosoft.bmp");
    if (bmp == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }


	// Sound init
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
    	//printf("Mix_OpenAudio: %s\n", Mix_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio Error: %s\n", SDL_GetError());
    	return EXIT_FAILURE;
	}
	
	int flags=MIX_INIT_OGG|MIX_INIT_MOD;
	int initted=Mix_Init(flags);
	if((initted&flags) != flags) {
	    //printf("Mix_Init: Failed to init required ogg and mod support!\n");
	    //printf("Mix_Init: %s\n", Mix_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init: %s\n", SDL_GetError());
    	return EXIT_FAILURE;
	}
    

	Mix_Music *music;
    music=Mix_LoadMUS("./ARTIST.S3M");
    if(!music) {
        //printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
        // this might be a critical error...
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadMUX: %s\n", SDL_GetError());
		return EXIT_FAILURE;
    }

	if(Mix_PlayMusic(music, 1)==-1) {
        //printf("Mix_PlayMusic: %s\n", Mix_GetError());
        // well, there's no music, but most games don't break without music...
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Mix_PlayMusic: %s\n", SDL_GetError());
    }

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
	    SDL_RenderCopy(ren, tex, nullptr, nullptr);
	    SDL_RenderPresent(ren);
		//SDL_Delay(250);
		//
	}


	// Cleanup
	//
	Mix_FreeMusic(music);
	
	Mix_Quit();
	Mix_CloseAudio();

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}
