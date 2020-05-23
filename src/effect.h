#pragma once
#include "texturemanager.h"

class Effect {
    private:
    protected:
        long unsigned int tick;
    public:
        Effect();
        virtual bool Apply(TextureManager * texture) = 0;
        virtual ~Effect() = 0;
};
