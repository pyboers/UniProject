#pragma once
#ifndef __Camera_H
#define __Camera_H
#include <GL/glew.h>
#include "../maths/vec3.h"
#include <string>
#include "../maths/mat4.h"
#include "../maths/Transform.h"

class Camera {

public:
	float horizontalangle;
	float verticalangle;
	int width, height;
	float fov;
	float znear;
	float zfar;
	float mousespeed;
	float movespeed;
	Transform transform;
	void update(float dt);
	Camera(float, float, float, int, int, float ,float ,float);
	int getHeight();
	int getWidth();
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	mat4 getViewProjection();
	~Camera();

};
#endif