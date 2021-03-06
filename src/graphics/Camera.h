#pragma once
#ifndef __Camera_H
#define __Camera_H
#include <GL/glew.h>
#include "../maths/vec3.h"
#include <string>
#include "../maths/mat4.h"

class Camera {
	int width, height;
	float fov;
	float znear;
	float zfar;
	float mousespeed;
	float movespeed;
	

public:	
	vec3 position;
	void update(float dt);
	Camera(float, float, float, int, int, float ,float ,float);
	int getHeight();
	int getWidth();
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	mat4 getViewProjection();
	~Camera();


private:
	float horizontalangle;
	float verticalangle;

};
#endif