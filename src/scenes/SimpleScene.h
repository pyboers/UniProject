//
// Created by Pierre-Yves Boers on 05/02/2018.
//

#pragma once
#ifndef UNIPROJECT_SIMPLESCENE_H
#define UNIPROJECT_SIMPLESCENE_H

#include "../engine/Scene.h"
#include "../graphics/Camera.h"
#include "../graphics/Shader.h"
#include "../physics/PhysicsWorld.h"
#include "../engine/Obj.h"
#include "../graphics/renderstage/RenderPipeline.h"
#include "../graphics/renderstage/SimpleRenderPipeline.h"

class SimpleScene : public Scene{
	Camera *camera;
	PhysicsWorld *pw;
	std::vector<Obj*> objects;
	SimpleRenderPipeline rp;
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
