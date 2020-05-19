#include <SDL2/SDL.h>
#include "texturemanager.h"

TextureManager::TextureManager(const char* file, SDL_Renderer* ren){
    this->tex = nullptr;
    this->sur = nullptr;
    this->ren = ren;
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "We are going to load: %s\n", file);
    SDL_Surface* bmp = SDL_LoadBMP(file);
    if (bmp == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        //TODO: Throw exception
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Creating surface. \n");
    this->sur = SDL_ConvertSurfaceFormat(bmp, SDL_PIXELFORMAT_ARGB8888, 0);
    if (this->sur == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_ConvertSurfaceFormat Error: %s\n", SDL_GetError());
        //TODO: Throw exception
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing bmp. \n");
    SDL_FreeSurface(bmp);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Creating Texture. \n");
    this->tex = SDL_CreateTexture(this->ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, this->sur->w, this->sur->h);
    if (this->tex == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTexture() Error: %s\n", SDL_GetError());
        //TODO: Throw Error.
    }
    

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Updating texture with surface.\n");
    this->Update();

    int w = 0;
    int h = 0;
    Uint32 format = 0;
    SDL_QueryTexture(this->tex, &format, NULL, &w, &h);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Format: %s\n", SDL_GetPixelFormatName(format));
}

TextureManager::TextureManager(const SDL_Rect sizerect, TextureColor color, SDL_Renderer* ren){
    Uint32 pixelColor;
    this->tex = nullptr;
    this->sur = nullptr;
    this->ren = ren;
    this->tex = SDL_CreateTexture(this->ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, sizerect.w, sizerect.h);
    if (this->tex == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTexture() Error: %s\n", SDL_GetError());
        //TODO: Throw Error.
    }
    // We create the input surface with the same especs
    this->sur = SDL_CreateRGBSurfaceWithFormat(0, sizerect.w, sizerect.h, 32, SDL_PIXELFORMAT_ARGB8888);
    if (this->sur == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRGBSurfaceWithFormat() failed: %s\n", SDL_GetError());
        //TODO: Throw exception
    }

    // Color the surface. Format is SDL_PIXELFORMAT_ARGB8888
    switch(color){
        case TEXTURE_BLACK:
            //pixelColor = ((0xFF<<24)|(0x00<<16)|(0x00<<8)|(0x00));
            pixelColor = SDL_MapRGBA(this->sur->format, 0,0,0,255);
            break;
        case TEXTURE_WHITE:
            //pixelColor = ((0xFF<<24)|(0xFF<<16)|(0xFF<<8)|(0xFF));
            pixelColor = SDL_MapRGBA(this->sur->format, 255,255,255,255);
            break;
        case TEXTURE_TRANS:
            //pixelColor = ((0x00<<24)|(0x00<<16)|(0x00<<8)|(0x00));
            pixelColor = SDL_MapRGBA(this->sur->format, 0,0,0,0);
            break;
        case TEXTURE_RED:
            pixelColor = SDL_MapRGBA(this->sur->format, 255,0,0,255);
            break;
        case TEXTURE_GREEN:
            pixelColor = SDL_MapRGBA(this->sur->format, 0,255,0,255);
            break;
        case TEXTURE_BLUE:
            pixelColor = SDL_MapRGBA(this->sur->format, 0,0,255,255);
            break;
    }

    if (SDL_FillRect(this->sur, NULL, pixelColor) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_FillRect() failed: %s\n", SDL_GetError());
    }

    // Update the texture with the surface with a blitting
    this->Update();
}

bool TextureManager::Render(const SDL_Rect* srcrect, const SDL_Rect* dstrect) {
    SDL_RenderCopy(this->ren, this->tex, srcrect, dstrect);
    return true;
}

SDL_Rect TextureManager::getSizeRect(){
    SDL_Rect size;
    size.x=0;
    size.y=0;
    if (this->tex == nullptr) {
        size.w=0;
        size.h=0;
    } else {
        int w, h;
        SDL_QueryTexture(this->tex, NULL, NULL, &w, &h);
        size.w=w;
        size.h=h;
    }
    return size;
}

SDL_Surface* TextureManager::getSurface(){
    return this->sur;
}

bool TextureManager::Update(){
    // Update the texture with the surface with a blitting
    // lock the texture
    void *texPixels;
    int pitch;    
    if (SDL_LockTexture(this->tex, NULL, &texPixels, &pitch) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't lock texture: %s\n", SDL_GetError());
        return false;
    }
    // Get the pixels information from the surface
    void *surPixels = this->sur->pixels;
    int surPitch = this->sur->pitch;
    // updated the texture with the pixels from the surface

    memcpy(texPixels, surPixels, (surPitch * this->sur->h));

    // unlock the texture
    SDL_UnlockTexture(this->tex);

    return true;
}

TextureManager::~TextureManager(){
    if (this->sur != nullptr) {
        SDL_FreeSurface(this->sur);
    }
    if (this->tex != nullptr) {
        SDL_DestroyTexture(this->tex);
    }
}
