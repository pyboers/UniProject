#include "Camera.h"

Camera::Camera(float x, float y, float z, int width, int height, float fov, float znear, float zfar) 
	: movespeed(100), horizontalangle(0), verticalangle(0.0), width(width), height(height), 
	mousespeed(0.1), transform(vec3(x, y, z)),  fov(fov), znear(znear), zfar(zfar) {
}

void Camera::update(float dt) {
	
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
