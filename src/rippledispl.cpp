//#include <vector>
#include <algorithm>
#include "rippledispl.h"
#include "texturemanager.h"
#include "fastsin.h"
#include <SDL2/SDL.h>

RippleDispl::RippleDispl(const int w, const int speed){
    //this->linebuf = new std::vector<Uint32>(w, (Uint32)0xFFFFFFFF);
    this->buffa = new Uint32[w];
    this->buffb = new Uint32[w];
    for (int i = 0; i < w; i++){
        this->buffa[i] = 0xFFFFFFFF;
        this->buffb[i] = 0xFFFFFFFF;
    }
    this->speed = speed;
    this->bounce = new FastSin(480, 64);
    //TODO: make this with only one buffer
}

RippleDispl::~RippleDispl(){
    //delete this->linebuf;
    delete [] this->buffa;
    delete [] this->buffb;
    delete bounce;
}

bool RippleDispl::Apply(TextureManager * texture){
    tick++;
    SDL_Surface* sur = texture->getSurface();
    void* pixels = sur->pixels; // pointer to the first value of the pixeldata
    void* cursor = pixels; // cursor for pointing to the data
    int pitch = sur->w; // pitch is the lenght in Uint32 of one row
    int h = sur->h; // height of the surface (number of pitch lenghts)
    
    // modify pixels here
    if (SDL_MUSTLOCK(sur)){
        SDL_LockSurface(sur);
    }

    // for each line...
    for (int line=0; line<h; line++){

        int displ = this->speed + bounce->isin(line+tick); 

        while (displ >= pitch){
            displ -= pitch;
        }
        while (displ <= -pitch){
            displ += pitch;
        }

        if (displ < 0) {
            displ = pitch + displ;
        }
        
        // we assume cursor is at the beggining of the line and line lenght is pitch (Uint32)
        Uint32 * start = (Uint32 *)cursor;
        Uint32 * end = (Uint32 *)cursor + pitch - 1;

        // big slice
        Uint32 * bigstart = start;
        Uint32 * bigend = end - displ;
        // small slice
        Uint32 * smallstart = bigend + 1;
        Uint32 * smallend = end;

        //memcopy to buffa and buffb
        std::copy(bigstart, bigend + 1, this->buffa);
        std::copy(smallstart, smallend + 1, this->buffb);

        // copy back to surface
        Uint32 * buffbend = this->buffb + displ - 1;
        Uint32 * buffaend = this->buffa + pitch - displ - 1;
        // small to beggining
        std::copy(this->buffb, buffbend + 1, (Uint32 *)cursor);
        // big to rear
        std::copy(this->buffa, buffaend + 1, (Uint32 *)cursor + displ );

        // move cursor to following line
        cursor = static_cast<Uint32*>(cursor) + pitch;

        /*
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
        */

    }


    if (SDL_MUSTLOCK(sur)){
        SDL_UnlockSurface(sur);
    }

    return true;
}
