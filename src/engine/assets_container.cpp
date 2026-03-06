#include <engine.hpp>

//Inserisci assets nel container
AssetsContainer& AssetsContainer::add(const std::string name,const std::string path){
    container.emplace(make_pair(name,new Asset(path)));
    return *this;
}

//Cerca e restituisce un puntatore al asset associato al nome, se non presente ritorna nullptr
Asset* AssetsContainer::find(std::string name){
    if(auto result = container.find(name); result != container.end()){
        return result->second;
    }
    return nullptr;
}


void AssetsContainer::init_textures(SDL_Renderer * render){
    for(auto& asset:container){
        asset.second->loadTexture(render);
    }
}