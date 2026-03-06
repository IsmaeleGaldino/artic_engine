#include <engine.hpp>

#define EXIT true
#define CONTINUE false
#define W_CAM 1280
#define H_CAM 960

//Costruttore dell'Engine, inizializza SDL
Engine::Engine(){
    SDL_Init(SDL_INIT_VIDEO); 
    camera = Camera(1280,1280,W_CAM,H_CAM);
    scena = Scene();
    window = SDL_CreateWindow("Engine Prototype",480,320,0);
    renderer = SDL_CreateRenderer(window,NULL);
}

//Distruttore dell'Engine, dealloca le strutture usate da SDL
Engine::~Engine(){
    SDL_Quit();
}

//Metodo per avviare l'engine
void Engine::run(){
    preRender();
    while(eventLoop()==CONTINUE){
        camera.update(100,2500);
        render();
    };
}



//Metodo che gestisce gli eventi
bool Engine::eventLoop(){
    SDL_Event event;
    const bool * keys = SDL_GetKeyboardState(nullptr);
    SDL_PollEvent(&event);
    if(event.type==SDL_EVENT_QUIT)
        return EXIT;
    if(keys[SDL_SCANCODE_W])
        camera.addVelY(-5);
    if(keys[SDL_SCANCODE_S])
        camera.addVelY(5);
    if(keys[SDL_SCANCODE_A])
        camera.addVelX(-5);
    if(keys[SDL_SCANCODE_D])
        camera.addVelX(5);
    return CONTINUE;
}

//Metodo che configura il rendering
void Engine::preRender(){
    scena.load();
    scena.loadTextures(renderer);
    SDL_SetWindowFullscreen(window,true);
    SDL_SyncWindow(window);
    SDL_SetRenderLogicalPresentation(renderer,W_CAM,H_CAM,SDL_LOGICAL_PRESENTATION_STRETCH);
}

//Metodo che effettua il rendering
void Engine::render(){
    SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    scena.display(renderer,&camera);
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
}