//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#pragma once
#ifndef UNIPROJECT_RENDERSTAGE_H
#define UNIPROJECT_RENDERSTAGE_H

#include "RenderPipeline.h"

class RenderStage{
protected:
	RenderPipeline *pipeline;
public:

	void setRenderPipeline(RenderPipeline *pipeline){
		this->pipeline = pipeline;
	}


	virtual void reset() = 0;
	virtual void bind(){

	} //This serves to allow outside drawing to its output buffer
	virtual void render() = 0;

	virtual ~RenderStage() = default;


};
#endif //UNIPROJECT_RENDERSTAGE_H
