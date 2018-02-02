//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_RENDERPIPELINE_H
#define UNIPROJECT_RENDERPIPELINE_H
class RenderPipeline{
	virtual void update(float dt) = 0;

	virtual void render(float dt) = 0;
};
#endif //UNIPROJECT_RENDERPIPELINE_H
