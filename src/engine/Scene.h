//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_SCENE_H
#define UNIPROJECT_SCENE_H

class Scene{
public:
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void input(float dt) = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
};
#endif //UNIPROJECT_SCENE_H
