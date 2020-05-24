#include <SDL2/SDL.h>
//#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <iostream>
//#include <stdio.h>
#include "sdlmanager.h"
#include "texturemanager.h"
#include "effect.h"
#include "hdispl.h"

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
    Effect * hdispl = new HDispl(texture->getW());

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
        hdispl->Apply(texture);
        texture->Update();
        texture->Render(nullptr, nullptr);
	    SDL_RenderPresent(ren);
		//SDL_Delay(250);
		//
	}

    delete hdispl;
    delete texture;
    delete sdlman;
    return EXIT_SUCCESS;
}
