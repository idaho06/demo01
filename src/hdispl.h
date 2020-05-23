#pragma once
#include "effect.h"
#include "texturemanager.h"

class HDispl: public Effect {
    private:
    protected:
    public:
        HDispl();
        ~HDispl();
        bool Apply(TextureManager * texture);
};
