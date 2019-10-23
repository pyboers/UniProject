#pragma once
#ifndef __FBO_H
#define __FBO_H
#include "GL/glew.h"
#include "Texture.h"

class FBO {
private:
	GLuint id;
	int width;
	int height;

	GLuint depthid;
public:
	FBO(int width, int height);
	~FBO();

	void bind();
	Texture *colorTextureAttachment(int slot);
	void depthBufferAttachment();
	Texture *depthTextureAttachment();

	static void bindWindow(int width, int height);


};
#endif