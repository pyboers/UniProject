//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#ifndef UNIPROJECT_SIMPLERENDERPIPELINE_H
#define UNIPROJECT_SIMPLERENDERPIPELINE_H


#include "RenderPipeline.h"
#include "ShadowStage.h"
#include "SceneStage.h"
#include "PostStage.h"

class SimpleRenderPipeline : public RenderPipeline{
	ShadowStage shadowStage;
	SceneStage sceneStage;
	PostStage postStage;
	Camera *camera;
	std::vector<PortalObj *> *portals;
public:
	SimpleRenderPipeline();

	void render() override;

	void setCamera(Camera * camera);

	void setPortals(std::vector<PortalObj*> *portals);

	~SimpleRenderPipeline() override;
};


#endif //UNIPROJECT_SIMPLERENDERPIPELINE_H
