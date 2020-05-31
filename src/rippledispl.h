#pragma once
#include "fastsin.h"
//#include <vector>
#include "effect.h"
#include "texturemanager.h"

class RippleDispl: public Effect {
    private:
        //std::vector<Uint32> * linebuf;
        FastSin * bounce;
        Uint32 * buffa;
        Uint32 * buffb;
        int speed;
    protected:
    public:
        RippleDispl(const int w, const int speed);
        ~RippleDispl();
        bool Apply(TextureManager * texture);
};
