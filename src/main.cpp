#include <iostream>
#include <SDL2/SDL.h>
#include <gl/glew.h>
#include "engine/Engine.h"
#include "scenes/SimpleScene.h"

SDL_Window *window;
int initWindow(int width, int height){
    if(SDL_Init(SDL_INIT_VIDEO)){//Attempt initialize
        return 1;
    }
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); //4.1 openGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    if(!SDL_GL_CreateContext(window)){
        return 1;
    }
    glewExperimental = GL_TRUE;
    GLenum error;
    if((error = glewInit())){
        return 1; //failed
    }


    SDL_GL_SetSwapInterval(0);//sync window cycle
    SDL_ShowWindow(window);
}


int main() {
    Engine &e = Engine::getEngine();
    e.init(1280, 720);
    e.pushScene(new SimpleScene());
    e.start();
}