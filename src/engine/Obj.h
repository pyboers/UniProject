//
// Created by Pierre-Yves Boers on 04/04/2018.
//

#ifndef UNIPROJECT_OBJ_H
#define UNIPROJECT_OBJ_H


#include "../graphics/Mesh.h"
#include "../maths/Transform.h"
#include "../graphics/Shader.h"

class Obj {
protected:
	Transform transform;
	Mesh &mesh;
public:
	Obj(Transform transform, Mesh &mesh);
	virtual void update(float dt);
	void render(Shader& shader);

	Transform& getTransform();
	const Mesh& getMesh() const;
};


#endif //UNIPROJECT_OBJ_H
