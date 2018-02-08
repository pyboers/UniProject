//
// Created by Pierre-Yves Boers on 05/02/2018.
//
#include <SDL_timer.h>
#include <SDL_video.h>
#include <SDL.h>
#include "Engine.h"

Engine::~Engine() {
	while(!scenes.empty()){
		delete popScene();
	}
}

Scene *Engine::swapScene(Scene *scene) {
	Scene *prevScene = scenes.back(); //get previous scene
	scenes.pop_back(); //pop scene off stack
	prevScene->stop(); //stop previous scene
	scenes.push_back(scene); //push the new scene onto the stack
	scene->start(); //start the new scene
	return prevScene;
}

void Engine::pushScene(Scene *scene) {
	if(!scenes.empty()){
		scenes.back()->pause(); //pause previous scene
	}
	scenes.push_back(scene); //push new scene onto stack
	scene->start(); //start new scene
}

Scene *Engine::popScene() {
	Scene *scene = scenes.back(); //get scene
	scenes.pop_back(); //pop scene of the stack
	return scene;
}

void Engine::start() {
	mainLoop = true;
	long lastTick = SDL_GetTicks();

	// main loop
	while (mainLoop) {
		SDL_Event e;
		while(SDL_PollEvent(&e) != 0){
			if(e.type == SDL_QUIT){
				 stop();
			}
		}
		long currentTick = SDL_GetTicks();
		float dt = (currentTick - lastTick)/1000.0f;

		//update input
		if(!scenes.empty()) {
			Scene *currentScene = scenes.back();
			currentScene->input(dt);
			currentScene->update(dt);
			currentScene->render();
		}
		SDL_GL_SwapWindow(window);
	}
}

void Engine::stop() {
	mainLoop = false;
}

void Engine::init(int windowWidth, int windowHeight) {
	if(SDL_Init(SDL_INIT_VIDEO)){//Attempt initialize
		printf("Error! Could not initialize SDL_Video");
	}
	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1); //4.1 openGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	if(!SDL_GL_CreateContext(window)){
		printf("Error couldn't create openGL context!");
	}
	glewExperimental = GL_TRUE;
	GLenum error;
	if((error = glewInit())){
		printf("Error couldn' init glew!");
	}


	SDL_GL_SetSwapInterval(0);//sync window cycle
	SDL_ShowWindow(window);
	glFrontFace(GL_CCW);
}

Engine::Engine() {

}

