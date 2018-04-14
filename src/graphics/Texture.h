//
// Created by Pierre-Yves Boers on 10/04/2018.
//

#ifndef UNIPROJECT_TEXTURE_H
#define UNIPROJECT_TEXTURE_H


#include <GL/glew.h>

class Texture { //This class acts as a wrapper for the opengl texture. This is to allow deletion of textures using the delete keyword instead of opengl's.
	GLuint texID;
public:
	Texture(Texture&) = delete; //No copies. Otherwise we could accidentally delete a texture referenced elsewhere
	Texture(int texID): texID(texID){

	}

	void bind(int slot) const{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, texID);
	}

	~Texture(){
		glDeleteTextures(1, &texID);
	}

};


#endif //UNIPROJECT_TEXTURE_H
