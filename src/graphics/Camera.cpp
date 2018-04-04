#include "Camera.h"
#include "../engine/Engine.h"

Camera::Camera(float x, float y, float z, int width, int height, float fov, float znear, float zfar) 
	: movespeed(2), horizontalangle(0), verticalangle(0.0), width(width), height(height),
	mousespeed(0.01), transform(vec3(x, y, z)),  fov(fov), znear(znear), zfar(zfar) {
}

void Camera::update(float dt) {
	vec3 look = vec3(sin(horizontalangle), 0, -cos(horizontalangle));
	vec3 perplook = vec3::getCrossProduct(look, vec3(0, 1, 0));
	if(Engine::getEngine().getInput().isDown(KEY_W)){
		transform.addToPos(look * movespeed * dt, this);
	}
	if(Engine::getEngine().getInput().isDown(KEY_S)){
		transform.addToPos((-look) * movespeed * dt, this);
	}
	if(Engine::getEngine().getInput().isDown(KEY_A)){
		transform.addToPos((-perplook) * movespeed * dt, this);
	}
	if(Engine::getEngine().getInput().isDown(KEY_D)){
		transform.addToPos(perplook * movespeed * dt, this);
	}
	if(Engine::getEngine().getInput().isDown(KEY_SPACE)){
		transform.addToPos(vec3(0, 1, 0) * movespeed * dt, this);
	}
	if(Engine::getEngine().getInput().isDown(KEY_LSHIFT)){
		transform.addToPos(vec3(0, -1, 0) * movespeed * dt, this);
	}
	verticalangle += Engine::getEngine().getInput().getMouseDY() * mousespeed;
	horizontalangle += Engine::getEngine().getInput().getMouseDX() * mousespeed;
	verticalangle = math::clamp(verticalangle, -PI/2.f, PI/2.f);
}
int Camera::getHeight() {
	return height;
}

int Camera::getWidth() {
	return width;
}

mat4 Camera::getViewMatrix(){
	mat4 translationM = mat4();
	mat4 rotationM = mat4();
	translationM.initTranslation(-transform.getPos().getX(), -transform.getPos().getY(), -transform.getPos().getZ());
	rotationM.initRotation(verticalangle, horizontalangle, 0);

	return rotationM * translationM;
}

mat4 Camera::getProjectionMatrix(){
	mat4 projection;
	projection.initPerspective(fov, width / (float)height, znear, zfar);
	return projection;
}

mat4 Camera::getViewProjection() {
	mat4 view = getViewMatrix();
	mat4 projection = getProjectionMatrix();
	return projection * view;
}


Camera::~Camera() {

}
