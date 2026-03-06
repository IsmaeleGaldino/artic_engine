#include <engine.hpp>

#define MAX_ACC 20
#define MAX_FOV 0.10

Camera::Camera() = default;

Camera::Camera(float x,float y,float w,float h){
    cam = {.x=x,.y=y,.w=w,.h=w};
    needupdate=false;
    velX=0;
    velY=0;
}

SDL_FRect Camera::getCamera(){
    return cam;
}



void Camera::update(float lowerbound, float upperbound){
    if(needupdate){
        if(cam.x+velX > lowerbound && cam.x+velX<upperbound){
            cam.x+=velX;
        } else{
            if(velX>0)
                cam.x=upperbound;
            else if(velX<0)
                cam.x=lowerbound;
        }
        if(cam.y+velY > lowerbound && cam.y+velY<upperbound){
            cam.y+=velY;
        }  else{
            if(velY>0)
                cam.y=upperbound;
            else if(velY<0)
                cam.y=lowerbound;
        }

        if(velX=velX/1.1;abs(velX)<0.2){
            velX=0;
        }
        if(velY=velY/1.1;abs(velY)<0.2){
            velY=0;
        }
        if(velX == 0 && velY == 0){
            SDL_Log("velocità azzerate\n");
            needupdate=false;
        }

    }
}

void Camera::addVelX(float x){
    velX=fmax(-MAX_ACC,fmin(velX+x,MAX_ACC));
    needupdate=true;
}

void Camera::addVelY(float y){
    velY=fmax(-MAX_ACC,fmin(velY+y,MAX_ACC));
    needupdate=true;
}