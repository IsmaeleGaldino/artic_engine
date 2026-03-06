#include <engine.hpp>

//Costruttore di Object, prende in input un puntatore all'objectAsset associato e un rettangolo per indicare la zona dove verrà renderizzato
Object::Object(Asset * asset , float x, float y, size_t z){
    this->asset=asset;
    this->x=x;
    this->y=y;
    this->z=z;
    h=32;
    w=32;
    render_dst = {.x=x,.y=y,.w=w,.h=h};
    render_src = {.x=0,.y=0,.w=32,h=32};
}


//Metodo che renderizza l'Object
void Object::draw(SDL_Renderer * renderer,SDL_FRect cam){
    render_dst.x=x-cam.x;
    render_dst.y=y-cam.y;
    SDL_RenderTexture(renderer,asset->getTexture(),&render_src,&render_dst);
}

float Object::getX(){
    return x;
}
float Object::getY(){
    return y;
}
size_t Object::getZ(){
    return z;
}
