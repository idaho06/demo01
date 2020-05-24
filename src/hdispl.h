#pragma once
//#include <vector>
#include "effect.h"
#include "texturemanager.h"

class HDispl: public Effect {
    private:
        //std::vector<Uint32> * linebuf;
        Uint32 * buffa;
        Uint32 * buffb;
        int speed;
    protected:
    public:
        HDispl(const int w, const int speed);
        ~HDispl();
        bool Apply(TextureManager * texture);
};
