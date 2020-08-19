#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <iostream>
//#include <stdio.h>
#include "sdlmanager.h"
#include "texturemanager.h"
#include "effect.h"
#include "hdispl.h"
#include "rippledispl.h"
#include "surface.h"

#define HRES 640
#define VRES 480

int main(int argv, char** args)
{
    SDLManager * sdlman = new SDLManager();
    SDL_Renderer* ren = sdlman->getRenderer();

    TextureManager * texture = new TextureManager("./akinosoft.bmp", ren);
    //SDL_Rect size;
    //size.w = HRES;
    //size.h = VRES;
    //TextureManager * texture = new TextureManager(size,TEXTURE_GREEN, ren);

    sdlman->loadPlayMusic("./ARTIST.S3M");

    // Load Horizontal displacement effect
    Effect * rdispl = new RippleDispl(texture->getW(), 0);

    // Load Backbroud image
    Effect * background = new Surface("./akinosoft.bmp");

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
        //SDL_RenderClear(ren);
        background->Apply(texture);
        rdispl->Apply(texture);
        texture->Update();
        texture->Render(nullptr, nullptr);
	    SDL_RenderPresent(ren);
		//SDL_Delay(1000/70);
		//
	}

    delete background;
    delete rdispl;
    delete texture;
    delete sdlman;
    return EXIT_SUCCESS;
}
