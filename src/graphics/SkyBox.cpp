#include "SkyBox.h"

SkyBox::SkyBox(Shader *s, int tid) : s(s), tid(tid) {
	
}

void SkyBox::display(mat4 *viewprojection) {
	glDisable(GL_DEPTH_TEST);
	s->bind();
	s->uniformMat4("vp", viewprojection);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tid);
	s->uniformi("cubeMap", 3);
	Mesh::indexCall(4);
	glEnable(GL_DEPTH_TEST);
}


