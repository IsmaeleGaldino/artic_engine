#include <engine.hpp>

//Costruttore che prende un path a un file .png e lo carica sulla Surface

Asset::Asset(){
    surface = NULL;
    texture = NULL;
}

Asset::Asset(const std::string path):surface(nullptr),texture(nullptr){
    surface = IMG_Load(path.c_str());
    
    if(surface==nullptr){
        SDL_Log("error on loading surface\n");
    }
}

Asset::~Asset(){
    if(!texture){
        SDL_DestroyTexture(texture);
    }
    if(!surface){
        SDL_DestroySurface(surface);
    }
}

//Metodo che utilizza la Surface per caricare la texture sulla scheda video
void Asset::loadTexture(SDL_Renderer * renderer){
    texture = SDL_CreateTextureFromSurface(renderer,surface);
}

SDL_Surface * Asset::getSurface(){
    return surface;
}

SDL_Texture * Asset::getTexture(){
    return texture;
}

