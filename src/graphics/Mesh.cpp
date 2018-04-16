#include "Mesh.h"
#include <iostream>

GLuint Mesh::indexingvao = 0;

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &vaoID);
	glDeleteBuffers(1, &vboID);
	glDeleteBuffers(1, &iboID);
}

void Mesh::load(GLfloat vertices[], GLuint indices[], GLuint vsize, GLuint isize, GLenum target) {
	this->target = target;
	this->size = isize;


	glGenVertexArrays(1,&vaoID);	// Generating Vertex Array
	glBindVertexArray(vaoID);	// Binding as current
	glGenBuffers(1, &vboID);	// Generating Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboID);	// Binding as an array buffer
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Inserting vertices into vbo.

	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 8 * sizeof(GLfloat), 0); //Attribute 0 has 3 non normalized floats in chunks of 8 with an offset of 0. Vertex Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, 0, 8 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat))); //Attribute 1 has 2 non normalized floats in chunks of 8 with an offset of 3 floats to skip the vertices. Texture Attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, 0, 8 * sizeof(GLfloat), (const void *)(5 * sizeof(GLfloat))); //Attribute 2 has 3 non normalized floats in chunks of 8 with an offset of 5 floats to skip the vertices and texture coords. Normal Attribute

	glGenBuffers(1, &iboID);	// Generating Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);	// Binding as an element array buffer. To contain indices.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize * sizeof(GLuint), indices, GL_STATIC_DRAW); // Inserting indices into ibo.

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void Mesh::draw() {
	glBindVertexArray(vaoID);
	glDrawElements(target, size, GL_UNSIGNED_INT, 0);
}


void Mesh::loadModel(char *filename) {
	FILE *f = fopen(filename, "r"); // open file
	if (!f) {
		printf("Could not open file");
		return;
	}
	char buffer[0xFF];
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> tex;
	std::vector<float> vertexdata; 
	while (fgets(buffer, 0xFF, f)) {
		char type[3];
		float x;
		float y;
		float z;
		sscanf(buffer, "%2s %f %f %f", type, &x, &y, &z);
		if (!strcmp(type, "v")) {
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		} else if(!strcmp(type, "vt")){
			tex.push_back(x);
			tex.push_back(y);
		} else if (!strcmp(type, "vn")) {
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
		} else if (!strcmp(type, "f")) {
			int faces[9];
			sscanf(buffer, "%2s %d/%d/%d %d/%d/%d %d/%d/%d", type, &(faces[0]), &(faces[1]), &(faces[2]),
				&(faces[3]), &(faces[4]), &(faces[5]),
				&(faces[6]), &(faces[7]), &(faces[8]));
			int i;
			for (i = 6; i >= 0; i-= 3) {
				///vertex coords
				vertexdata.push_back(vertices[(faces[i]-1) * 3]);
				vertexdata.push_back(vertices[((faces[i] - 1) * 3) + 1]);
				vertexdata.push_back(vertices[((faces[i] - 1) * 3) + 2]);

				//uv coords
				vertexdata.push_back(tex[((faces[i + 1] - 1) * 2)]);
				vertexdata.push_back(tex[((faces[i + 1] - 1) * 2) + 1]);
				//normals
				vertexdata.push_back(normals[(faces[i + 2] - 1) * 3]);
				vertexdata.push_back(normals[((faces[i + 2] - 1) * 3) + 1]);
				vertexdata.push_back(normals[((faces[i + 2] - 1) * 3) + 2]);
				//Todo. Push string to vector. comparestr and dont add if not needed, construct indices as you do that
			}
		}
	}
	int vertexdatasize = vertexdata.size();
	unsigned int *indices = (unsigned int *)malloc(sizeof(unsigned int) * vertexdatasize);
	//Due to the way the file is being read.
	//The vertex data is put in the order of the indices specified,
	//causing the index array to simply be 0...n
	float *vertexdataarray = (float *)malloc(sizeof(float) * vertexdatasize);
	int i;
	for (i = 0; i < vertexdatasize; i++) {
		indices[i] = i;
		vertexdataarray[i] = vertexdata[i];
	}
	printf("Vertexdatasize: %d %s \n", vertexdatasize, filename);
	load(vertexdataarray, indices, vertexdatasize, vertexdatasize, GL_TRIANGLES);
}






























Mesh * Mesh::generateRectangularPrism() {
	//vertices for each index. In theory we only need 8 vertices of 3 coordinate floats 2 texture coordinates and 3 normal coordinates in other words 64 floats. 
	// However we want the normals of each vertex to depend on the face being drawn, which means we cannot reuse a vertex for a different face.
	float vertexarray[288] = {
		//Front
		-0.5, 0.5, -0.5, 0, 1, 0, 0, -1,
		-0.5, -0.5, -0.5, 0, 0, 0, 0, -1,
		0.5, -0.5, -0.5, 1, 0, 0, 0, -1,
		0.5, -0.5, -0.5, 1, 0, 0, 0, -1,
		0.5, 0.5, -0.5, 1, 1, 0, 0, -1,
		-0.5, 0.5, -0.5, 0, 1, 0, 0, -1,
		//Back
		0.5, -0.5, 0.5, 1, 0, 0, 0, 1,
		-0.5, -0.5, 0.5, 0, 0, 0, 0, 1,
		-0.5, 0.5, 0.5, 0, 1, 0, 0, 1,
		-0.5, 0.5, 0.5, 0, 1, 0, 0, 1,
		0.5, 0.5, 0.5, 1, 1, 0, 0, 1,
		0.5, -0.5, 0.5, 1, 0, 0, 0, 1,
		//Left
		-0.5, -0.5, 0.5, 0, 0, -1, 0, 0,
		-0.5, -0.5, -0.5, 1, 0, -1, 0, 0,
		-0.5, 0.5, -0.5, 1, 1, -1, 0, 0,
		-0.5, 0.5, 0.5, 0, 1, -1, 0, 0,
		-0.5, -0.5, 0.5, 0, 0, -1, 0, 0,
		-0.5, 0.5, -0.5, 1, 1, -1, 0, 0,

		//Right
		0.5, 0.5, -0.5, 1, 1, 1, 0, 0,
		0.5, -0.5, -0.5, 1, 0, 1, 0, 0,
		0.5, -0.5, 0.5, 0, 0, 1, 0, 0,
		0.5, 0.5, -0.5, 1, 1, 1, 0, 0,
		0.5, -0.5, 0.5, 0, 0, 1, 0, 0,
		0.5, 0.5, 0.5, 0, 1, 1, 0, 0,
		//Bottom
		-0.5, -0.5, -0.5, 0, 0, 0, -1, 0,
		-0.5, -0.5, 0.5, 0, 1, 0, -1, 0,
		0.5, -0.5, 0.5, 1, 1, 0, -1, 0,
		0.5, -0.5, -0.5, 1, 0, 0, -1, 0,
		-0.5, -0.5, -0.5, 0, 0, 0, -1, 0,
		0.5, -0.5, 0.5, 1, 1, 0, -1, 0,
		//Top
		0.5, 0.5, 0.5, 1, 1, 0, 1, 0,
		-0.5, 0.5, 0.5, 0, 1, 0, 1, 0,
		-0.5, 0.5, -0.5, 0, 0, 0, 1, 0,
		0.5, 0.5, 0.5, 1, 1, 0, 1, 0,
		-0.5, 0.5, -0.5, 0, 0, 0, 1, 0,
		0.5, 0.5, -0.5, 1, 0, 0, 1, 0,
	};


	int i;
	unsigned int indices[36];
	//Indices are put into counter clockwise order
	for (i = 0; i < 36; i++) {
		indices[i] = i;
	}

	Mesh *m = new Mesh();
	m->load(vertexarray, indices, 288, 36, GL_TRIANGLES);
	return m;
}

void Mesh::indexCall(int size) {
	if (!indexingvao) {
		glGenVertexArrays(1, &indexingvao);
	}
	glBindVertexArray(indexingvao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, size);
}

GLuint Mesh::getVAOID() const {
	return vaoID;
}

Mesh::Mesh() {

}
