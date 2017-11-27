#include "FBO.h"

FBO::FBO(int width, int height) : width(width), height(height) {
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER,id);
}

FBO::~FBO() {
	glDeleteFramebuffers(1, &id);
	glDeleteRenderbuffers(1, &depthid);
}

void FBO::bind() {
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}


int FBO::colorTextureAttachment(int slot) {
	GLuint texid;
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_FLOAT, 0);//create texture in memory
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	GLenum enums[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, enums);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, texid, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, texid, 0);

	return texid;
}

void FBO::depthBufferAttachment() {
	glGenRenderbuffers(1, &depthid);
	glBindRenderbuffer(GL_RENDERBUFFER, depthid);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthid);
}



void FBO::bindWindow(int width, int height) {
	glViewport(0, 0, width, height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}