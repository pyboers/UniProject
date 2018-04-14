//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#ifndef UNIPROJECT_SCENESTAGE_H
#define UNIPROJECT_SCENESTAGE_H


#include "RenderStage.h"
#include "../FBO.h"
#include "../Shader.h"
#include "../Camera.h"

class SceneStage : public RenderStage{
public:
	FBO *pre;
	Texture *pre_texture;
	Shader *basicShader;
	Camera *camera;
	SceneStage();

	void setCamera(Camera* camera);
	void render() override;

	~SceneStage() override;
};


#endif //UNIPROJECT_SCENESTAGE_H
