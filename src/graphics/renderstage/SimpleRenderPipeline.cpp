//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#include "SimpleRenderPipeline.h"

SimpleRenderPipeline::~SimpleRenderPipeline() {
	RenderPipeline::~RenderPipeline();
}

SimpleRenderPipeline::SimpleRenderPipeline() {
	shadowStage.setRenderPipeline(this);
	sceneStage.setRenderPipeline(this);
	postStage.setRenderPipeline(this);
}

void SimpleRenderPipeline::render() {
	shadowStage.bindDirectionalLight(dl);
	shadowStage.reset();
	shadowStage.render();

	sceneStage.reset();
	sceneStage.bindPortals(portals);
	sceneStage.render();

	postStage.setPreTexture(sceneStage.pre_texture);
	postStage.reset();
	postStage.render();
}

void SimpleRenderPipeline::setCamera(Camera *camera) {
	this->camera = camera;
	sceneStage.camera = camera;
}

void SimpleRenderPipeline::setPortals(std::vector<PortalObj*> *portals) {
	this->portals = portals;

}
