#include <vector>
#include <algorithm>
#include "hdispl.h"
#include "texturemanager.h"
#include <SDL2/SDL.h>

HDispl::HDispl(){
}

HDispl::~HDispl(){
}

bool HDispl::Apply(TextureManager * texture){
    tick++;
    SDL_Surface* sur = texture->getSurface();
    void* pixels = sur->pixels; // pointer to the first value of the pixeldata
    void* cursor = pixels; // cursor for pointing to the data
    int pitch = sur->pitch; // pitch is the lenght in bytes (char) of one row
    int h = sur->h; // height of the surface (number of pitch lenghts)
    

    std::vector<Uint8> linebuf(pitch, (Uint8)255); // initialize the line buffer
    
    // modify pixels here
    if (SDL_MUSTLOCK(sur)){
        SDL_LockSurface(sur);
    }

    // for each line...
    for (int line=0; line<h; line++){
        // copy one line of surface data to line buffer
        // We assume cursor points to beggining of line
        void* start = cursor;
        for (;(Uint8*)cursor<((Uint8*)start+pitch); cursor = static_cast<Uint8*>(cursor) + 1 ){
            linebuf.at((Uint8*)cursor-(Uint8*)start)=*(Uint8*)cursor;
        }
        
        // rotate data in the buffer
        std::rotate(linebuf.begin(), linebuf.begin() + 4, linebuf.end());
        // copy back buffer to the surface  
        // let's reset cursor to start of the line
        cursor = start;
        for (;(Uint8*)cursor<((Uint8*)start+pitch); cursor = static_cast<Uint8*>(cursor) + 1 ){
            *(Uint8*)cursor = linebuf.at((Uint8*)cursor-(Uint8*)start);
        }


    }


    if (SDL_MUSTLOCK(sur)){
        SDL_UnlockSurface(sur);
    }

    return true;
}
