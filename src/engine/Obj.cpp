//
// Created by Pierre-Yves Boers on 04/04/2018.
//

#include "Obj.h"
#include "../graphics/Shader.h"

Obj::Obj(Transform transform, Mesh &mesh, Texture* t) : transform(transform), mesh(mesh), texture(t){

}

void Obj::render(Shader& shader) {
	mat4 model = transform.getMatrix();
	shader.uniformMat4("model", &model);
	texture->bind(0);
	shader.uniformi("diffuseMap", 0);
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
