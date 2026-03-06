#include <engine.hpp>

ChunksRender::ChunksRender(size_t x_chunks, size_t y_chunks, size_t z_chunks, size_t sizeofchunk){
    this->x_chunks=x_chunks;
    this->y_chunks=y_chunks;
    this->z_chunks=z_chunks;
    this->sizeofchunk=sizeofchunk;
    for(size_t i =0 ; i<x_chunks*y_chunks*z_chunks;i++){
        chunks.push_back(std::list<Object*>());
    }
}

//Metodo per calcolare l'index di un chunk usando le coordinate x,y
size_t ChunksRender::getIndex(float x,float y){
    return (floor(x/sizeofchunk)*z_chunks) + (floor(y/sizeofchunk)*z_chunks*x_chunks);
}

//Metodo per prendere il chunk x,y.
size_t ChunksRender::getIndex(size_t x,size_t y){
    return (x*z_chunks) + (y*z_chunks*x_chunks);
}

ChunksRender& ChunksRender::loadObject(Object * obj){
    float x = obj->getX();
    float y = obj->getY();
    size_t z = obj->getZ();

    if(x>=0 && y>=0 && z>=0 && 
        x<=(x_chunks*sizeofchunk) && 
        y<=(y_chunks*sizeofchunk) && 
        z<=(z_chunks*sizeofchunk))
    {
        chunks[getIndex(x,y)+z].push_back(obj);
    }
    else {
        SDL_Log("stai aggiungendo un object fuori dal mondo\n");
    }
    return *this;
}


void ChunksRender::render(SDL_Renderer * renderer,Camera * camera){
    SDL_FRect cam = camera->getCamera();
    int range = ceil(cam.w/sizeofchunk);
    size_t x,y;
    x=floor((cam.x+(cam.w/2))/sizeofchunk);
    y=floor((cam.y+(cam.h/2))/sizeofchunk);
    //SDL_Log("range:%d  xcam:%d  ycam:%d \n",range,x,y);
    for(int i=-range;i<=range;i++){
        for(int j=-range;j<=range;j++){
            if(x+i < 0 || y+j < 0 || x+i >= x_chunks || y+j >= y_chunks)
                continue;
            for(size_t z=0;z<z_chunks;z++){
                for(auto& object:chunks[getIndex(x+i,y+j)+z]){
                    object->draw(renderer,cam);
                }
            }
        }
    }
}
