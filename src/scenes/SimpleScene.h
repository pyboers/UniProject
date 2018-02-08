//
// Created by Pierre-Yves Boers on 05/02/2018.
//

#pragma once
#ifndef UNIPROJECT_SIMPLESCENE_H
#define UNIPROJECT_SIMPLESCENE_H

#include "../engine/Scene.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"

class SimpleScene : public Scene{
	Camera *camera;
	Shader *basicShader;
public:
	void start() override;
	void stop() override;
	void pause() override;
	void resume() override;
	void input(float dt) override;
	void update(float dt) override;
	void render() override;
};
#endif //UNIPROJECT_SIMPLESCENE_H
