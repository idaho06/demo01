#include <vector>
#include <algorithm>
#include "hdispl.h"
#include "texturemanager.h"
#include <SDL2/SDL.h>

HDispl::HDispl(const int w){
    this->linebuf = new std::vector<Uint32>(w, (Uint32)0xFFFFFFFF);
}

HDispl::~HDispl(){
    delete this->linebuf;
}

bool HDispl::Apply(TextureManager * texture){
    tick++;
    SDL_Surface* sur = texture->getSurface();
    void* pixels = sur->pixels; // pointer to the first value of the pixeldata
    void* cursor = pixels; // cursor for pointing to the data
    int pitch = sur->w; // pitch is the lenght in bytes (char) of one row
    int h = sur->h; // height of the surface (number of pitch lenghts)
    
    // modify pixels here
    if (SDL_MUSTLOCK(sur)){
        SDL_LockSurface(sur);
    }

    // for each line...
    for (int line=0; line<h; line++){
        // copy one line of surface data to line buffer
        // We assume cursor points to beggining of line
        void* start = cursor;
        for (;(Uint32*)cursor<((Uint32*)start+pitch); cursor = static_cast<Uint32*>(cursor) + 1 ){
            this->linebuf->at((Uint32*)cursor-(Uint32*)start)=*(Uint32*)cursor;
        }
        
        // rotate left data in the buffer
        std::rotate(this->linebuf->begin(), this->linebuf->begin() + 1, this->linebuf->end());
        // copy back buffer to the surface  
        // let's reset cursor to start of the line
        cursor = start;
        for (;(Uint32*)cursor<((Uint32*)start+pitch); cursor = static_cast<Uint32*>(cursor) + 1 ){
            *(Uint32*)cursor = this->linebuf->at((Uint32*)cursor-(Uint32*)start);
        }


    }


    if (SDL_MUSTLOCK(sur)){
        SDL_UnlockSurface(sur);
    }

    return true;
}
