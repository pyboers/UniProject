#pragma once
#ifndef __Mesh_H
#define __Mesh_H
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <vector>;
#include "../maths/vec3.h"

class Mesh {
	GLuint vaoID;
	GLuint vboID;
	GLuint iboID;
	GLuint size;
	GLenum target;

	static GLuint indexingvao;
public:
	Mesh(Mesh &mesh) = delete;
	Mesh();
	~Mesh(); //THIS WILL PREVENT MULTIPLE COPIES. BEWARE!
	void load(GLfloat vertices[], GLuint indices[], GLuint vsize, GLuint isize, GLenum target);
	void draw();
	void loadModel(char *filename);

	static Mesh * generateRectangularPrism();

	static void indexCall(int size);

	GLuint getVAOID() const;
};
#endif