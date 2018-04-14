//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#include "SimpleRenderPipeline.h"

SimpleRenderPipeline::~SimpleRenderPipeline() {
	RenderPipeline::~RenderPipeline();
}

SimpleRenderPipeline::SimpleRenderPipeline() : shadowStage(), sceneStage(), postStage(){
	shadowStage.setRenderPipeline(this);
	sceneStage.setRenderPipeline(this);
	postStage.setRenderPipeline(this);
	postStage.setPreTexture(sceneStage.pre_texture);
}

void SimpleRenderPipeline::render() {
	shadowStage.render();
	sceneStage.render();
	postStage.render();
}

void SimpleRenderPipeline::setCamera(Camera *camera) {
	this->camera = camera;
	sceneStage.camera = camera;
}
