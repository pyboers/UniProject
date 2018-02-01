//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_ENGINE_H
#define UNIPROJECT_ENGINE_H

#include <vector>
#include "Scene.h"

class Engine {
private:
	std::vector<Scene> scenes;

	Engine();

public:
	/*
	 * Singleton functions
	 */
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
	Scene*  swapScene(Scene* scene);
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
	void update(float dt);
	void input(float dt);
	void render();


};
#endif //UNIPROJECT_ENGINE_H