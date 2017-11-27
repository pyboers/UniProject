#include <iostream>
#include <SDL2/SDL.h>
#include <gl/glew.h>

int main() {
    if(SDL_Init(SDL_INIT_VIDEO)){//Attempt initialize
        return 1;
    }
    SDL_Window *window;
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); //4.1 openGL
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    if(!SDL_GL_CreateContext(window)){
        //sdlgeterror
        return 1;
    }
    glewExperimental = GL_TRUE;
    GLenum error;
    if((error = glewInit())){
        return 1; //failed
    }


    SDL_GL_SetSwapInterval(0);//sync window cycle
    SDL_ShowWindow(window);
    while(true){
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                return 0;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        glRectf(0, 0, 1, 1);
        SDL_GL_SwapWindow(window);

    }
    return 0;
}