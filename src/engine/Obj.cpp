//
// Created by Pierre-Yves Boers on 04/04/2018.
//

#include "Obj.h"
#include "../graphics/Shader.h"

Obj::Obj(Transform transform, Mesh &mesh) : transform(transform), mesh(mesh){

}

void Obj::render(Shader& shader) {
	mat4 model = transform.getMatrix();
	shader.uniformMat4("model", &model);
	mesh.draw();
}

Transform &Obj::getTransform() {
	return transform;
}

const Mesh &Obj::getMesh() const {
	return mesh;
}

void Obj::update(float dt) {

}
