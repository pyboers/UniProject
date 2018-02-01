//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_SCENE_H
#define UNIPROJECT_SCENE_H
class Scene{

public:
	void start();
	void stop();
	void pause();
	void resume();
	void input(float dt);
	void update(float dt);
	void render();
};
#endif //UNIPROJECT_SCENE_H
