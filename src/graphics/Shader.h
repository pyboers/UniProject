#pragma once
#ifndef __SHADER_H
#define __SHADER_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "../maths/mat4.h"
#include "../maths/vec3.h"
class Shader{
private:
	GLuint programId;
	GLuint vsId;
	GLuint fsId;
	Shader(GLuint programId, GLuint vsId, GLuint fsId) 
		: programId(programId), vsId(vsId), fsId(fsId) {}

public:
	static Shader *load(GLchar *vsname, GLchar *fsname);
	void bind();
	int getUniformLocation(char *name);
	void uniformMat4(char *name, mat4 *m);
	void uniformVec3(char *name, vec3 *v);
	void uniformVec2(char *name, float f1, float f2);
	void uniformVec4(char *name, float x, float y, float z, float w);
	void uniformVec4(char *name, vec4 *v);
	void uniformf(char *name, float);
	void uniformi(char *name, int);
	~Shader();
};

#endif