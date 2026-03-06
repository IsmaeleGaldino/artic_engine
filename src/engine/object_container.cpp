#include <engine.hpp>

ObjectContainer& ObjectContainer::add(std::string name, Asset * asset, float x, float y, size_t z){
    container.emplace(make_pair(name,new Object(asset,x,y,z)));
    return *this;
}

Object* ObjectContainer::find(std::string name){
    if(auto result = container.find(name); result!= container.end()){
        return result->second;
    }
    return nullptr;
}