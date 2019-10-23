//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#ifndef UNIPROJECT_POSTSTAGE_H
#define UNIPROJECT_POSTSTAGE_H


#include "RenderStage.h"

class PostStage : public RenderStage{
	Shader * postShader;
	const Texture *pre_texture; //Reference
public:
	PostStage();


	void render() override;
	void reset();

	void setPreTexture(const Texture* texture);

	~PostStage() override;
};


#endif //UNIPROJECT_POSTSTAGE_H
