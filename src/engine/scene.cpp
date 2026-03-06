#include <engine.hpp>

Scene::Scene() : chunks(ChunksRender(10,10,5,320)),gameAssetsContainer(),gameObjectsContainer(){}

void Scene::load(){
    gameAssetsContainer
        .add("blue","assets/blue.png")
        .add("green","assets/green.png")
        .add("orange","assets/orange.png")
        .add("purple","assets/purple.png")
        .add("red","assets/red.png")
        .add("white","assets/white.png");
    gameObjectsContainer
        .add("blue_0",gameAssetsContainer.find("blue"),1600,1600,1)
        .add("blue_1",gameAssetsContainer.find("blue"),2450,1600,2)
        .add("green_0",gameAssetsContainer.find("green"),1700,1400,1)
        .add("white_0",gameAssetsContainer.find("white"),1300,1850,1)
        .add("red_0",gameAssetsContainer.find("red"),1900,2100,1)
        .add("orange_0",gameAssetsContainer.find("orange"),1450,1200,1)
        .add("purple_0",gameAssetsContainer.find("purple"),1100,1700,1);
    chunks
        .loadObject(gameObjectsContainer.find("blue_0"))
        .loadObject(gameObjectsContainer.find("blue_1"))
        .loadObject(gameObjectsContainer.find("purple_0"))
        .loadObject(gameObjectsContainer.find("orange_0"))
        .loadObject(gameObjectsContainer.find("red_0"))
        .loadObject(gameObjectsContainer.find("white_0"))
        .loadObject(gameObjectsContainer.find("green_0"));
}

//Metodo che invoca i vari render delle varie classi, in questo caso solo del chunks
void Scene::display(SDL_Renderer * renderer,Camera * camera){
   chunks.render(renderer,camera);
}


void Scene::loadTextures(SDL_Renderer * renderer){
    gameAssetsContainer.init_textures(renderer);
}



