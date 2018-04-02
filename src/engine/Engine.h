//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_ENGINE_H
#define UNIPROJECT_ENGINE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <vector>
#include "Scene.h"
#include "Input.h"

class Engine {
private:
	std::vector<Scene *> scenes;
	bool mainLoop = false;
	SDL_Window *window;
	int windowWidth, windowHeight;
	Engine();

public:
	/*
	 * Singleton functions
	 */

	void init(int windowWidth, int windowHeight);

	Engine(Engine const &) = delete; //no copy constructor for singleton
	void operator=(Engine const &) = delete; //No assigning of the singleton

	~Engine();

	static Engine& getEngine(){
		static Engine instance;
		return instance;
	}
	/*
	 * StateManager functions
	 */
	/**
	 * Swaps scenes
	 * @param scene The replacement
	 * @return The removed scene(note this should be deleted/handled by the user)
	 */
	Scene* swapScene(Scene* scene);
	/**
	 * Pushes the scene on the stack
	 * @param scene New scene
	 */
	void pushScene(Scene* scene);
	/**
	 * Pops the scene of the stack
	 * @return the scene being popped. This should be handled/deleted by the user.
	 */
	Scene* popScene();

	/*
	 * Engine functions
	 */
	void start();
	void stop();

	int getWindowHeight();
	int getWindowWidth();


};
#endif //UNIPROJECT_ENGINE_H
