#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_events.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <string>
#include <cmath>


class Asset{
    private:
        SDL_Surface * surface;
        SDL_Texture * texture;
    public:
        Asset();
        Asset(const std::string);
        ~Asset();
        void loadTexture(SDL_Renderer *);
        SDL_Surface * getSurface();
        SDL_Texture * getTexture();
};

//Contenitore di Assets organizzato mediante Hashtable
class AssetsContainer{
    private:
        std::unordered_map<std::string,Asset*> container;
    public:
        AssetsContainer& add(const std::string name, const std::string path);
        Asset* find(std::string name);
        void init_textures(SDL_Renderer * render);
};

class Object{
    private:
        Asset * asset;
        float x,y,w,h;
        size_t z;
        SDL_FRect render_src;
        SDL_FRect render_dst;
    public:
        Object(Asset * asset,float x, float y, size_t z);
        void draw(SDL_Renderer *,SDL_FRect cam);
        float getX();
        float getY();
        size_t getZ();
};

//Contenitore di Objects
class ObjectContainer{
    private:
        std::unordered_map<std::string,Object*> container;
    public:
        ObjectContainer& add(std::string name,Asset * asset,float x,float y, size_t z);
        Object* find(std::string name);
};

class Camera{
    private:
        SDL_FRect cam;
        float velX,velY;  
        bool needupdate;
    public:
        Camera();
        Camera(float x,float y,float w,float h);
        SDL_FRect getCamera();
        void update(float upperbound, float lowerbound);
        void addVelX(float x);
        void addVelY(float y);
};


class ChunksRender{
    private:
        std::vector<std::list<Object*>> chunks;
        size_t x_chunks;
        size_t y_chunks;
        size_t z_chunks;
        size_t sizeofchunk;
        size_t getIndex(float x,float y);
        size_t getIndex(size_t x,size_t y);
    public:
        ChunksRender(size_t x_chunks, size_t y_chunks, size_t z_chunks,size_t sizeofchunk);
        ChunksRender& loadObject(Object * obj);
        void render(SDL_Renderer * rend,Camera * cam);
};

class Scene{
    private:
        ChunksRender chunks;
        ObjectContainer gameObjectsContainer;
        AssetsContainer gameAssetsContainer;
    public:
        Scene();
        void load();
        void display(SDL_Renderer *,Camera *);
        void loadTextures(SDL_Renderer *);
};

class Engine{
    private:    
        SDL_Window * window;
        SDL_Renderer * renderer;
        Scene scena;
        Camera camera;
        bool eventLoop();
        void preRender();
        void render();
    public:
        Engine();
        ~Engine();
        void run();
        
};
