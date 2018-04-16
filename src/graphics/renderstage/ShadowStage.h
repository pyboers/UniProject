//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#ifndef UNIPROJECT_SHADOWSTATE_H
#define UNIPROJECT_SHADOWSTATE_H


#include "RenderStage.h"
#include "../Shader.h"
#include "RenderPipeline.h"

class ShadowStage : public RenderStage {
private:
	Shader *shadowmapper;
	DirectionalLight *directionalLight;
public:
	explicit ShadowStage();


	void render() override;

	void reset();

	void bindDirectionalLight(DirectionalLight *directionalLight);

	~ShadowStage() override;
};


#endif //UNIPROJECT_SHADOWSTATE_H
