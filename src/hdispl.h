#pragma once
#include <vector>
#include "effect.h"
#include "texturemanager.h"

class HDispl: public Effect {
    private:
        std::vector<Uint32> * linebuf;
    protected:
    public:
        HDispl(const int w);
        ~HDispl();
        bool Apply(TextureManager * texture);
};
