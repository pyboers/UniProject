//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#ifndef UNIPROJECT_RENDERPIPELINE_H
#define UNIPROJECT_RENDERPIPELINE_H


#include <vector>
#include "../lighting/Light.h"
#include "../lighting/DirectionalLight.h"

class RenderPipeline {
public:
	std::vector<Light *> lights;
	DirectionalLight *dl;
	std::vector<Obj*> *objects;

	void addLight(Light * light){
		lights.push_back(light);
	}

	void setDirectionalLight(DirectionalLight * dl){
		this->dl = dl;
	}

	void setObjs(std::vector<Obj*> *objs){
		objects = objs;
	}

	virtual void render() = 0;

	virtual ~RenderPipeline(){
		for(auto *light : lights){
			delete light;
		}
		lights.clear();
		delete dl;
	}

};


#endif //UNIPROJECT_RENDERPIPELINE_H
