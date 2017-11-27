#include "Shader.h"

Shader::~Shader() {
	glDeleteProgram(vsId);
	glDeleteProgram(fsId);
	glDeleteProgram(programId);
}

static int loadFileInto(char * dest, char * name) {
	char buff[0xFF]; //max line length 255
	FILE *f = fopen(name, "r"); 
	if (!f) {
		printf("File won't say hello to world %s\n", name);
		return NULL;
	}
	while (fgets(buff, 0xFF, f)) {
		strcat(dest, buff);
	}
	fclose(f);
	return 1; 
}


Shader * Shader::load(char * vsname, char * fsname) {
	GLchar *vs, *fs;
	vs = (char *)calloc(0xFFFF, sizeof(char));
	fs = (char *)calloc(0xFFFF, sizeof(char));
	// load vertex shader
	if (!loadFileInto(vs, vsname)) {
		return nullptr;
	}
	// load fragment shader
	if (!loadFileInto(fs, fsname)) {
		return nullptr;
	}

	Shader * sd = new Shader(glCreateProgram(), glCreateShader(GL_VERTEX_SHADER), 
		glCreateShader(GL_FRAGMENT_SHADER));

	GLint length;
	const GLchar *vs_f = vs, *fs_f = fs;
	// compile vertex shader
	length = (GLint)strlen(vs);
	glShaderSource(sd->vsId, 1, &vs_f, &length);
	glCompileShader(sd->vsId);

	// compile fragment shader
	length = (GLint)strlen(fs);
	glShaderSource(sd->fsId, 1, &fs_f, &length);
	glCompileShader(sd->fsId);

	// Check compilation error
	int status;
	char errbuff[1024];
	glGetShaderiv(sd->vsId, GL_COMPILE_STATUS, &status); //get status
	if (!status) {
		glGetShaderInfoLog(sd->vsId, 1024, NULL, errbuff);	//get log
		printf("%s vertex shader couldn't be compiled: %s\n", vsname, errbuff);
		printf("VS Code: %s\n", vs);		//print contents of the vs code
		return nullptr;
	}

	glGetShaderiv(sd->fsId, GL_COMPILE_STATUS, &status); //get status
	if (!status) {
		glGetShaderInfoLog(sd->fsId, 1024, NULL, errbuff); //get log
		printf("%s fragment shader couldn't be compiled: %s\n", fsname, errbuff);
		printf("FS CODE: %s\n", fs);	//print contents of the vs code
		return nullptr;
	}

	glAttachShader(sd->programId, sd->vsId);  //Attaches vertex shader to the shader program
	glAttachShader(sd->programId, sd->fsId);  //Attaches fragment shader to the shader program	

	glLinkProgram(sd->programId);		//Connects the vertex shader to the fragment shader
	glGetProgramiv(sd->vsId, GL_COMPILE_STATUS, &status);	//Gets the status of the program
	if (!status) {
		glGetProgramInfoLog(sd->vsId, 1024, NULL, errbuff);
		printf("%s vertex shader couldn't link: %s\n", vsname, errbuff);
		return nullptr;
	}

	glValidateProgram(sd->programId);
	glGetProgramiv(sd->fsId, GL_COMPILE_STATUS, &status); //Gets the status of the program
	if (!status) {
		glGetProgramInfoLog(sd->fsId, 1024, NULL, errbuff);
		printf(" %s fragment shader couldn't link: %s\n", fsname, errbuff);
		return nullptr;
	}

	return sd;
}

void Shader::bind() {
	glUseProgram(programId);
}

int Shader::getUniformLocation(char * name) {

	return glGetUniformLocation(programId, name);
}

void Shader::uniformMat4(char * name, mat4 * m) {
	glUniformMatrix4fv(getUniformLocation(name), 1, 0, m->getData());
}

void Shader::uniformVec3(char * name, vec3 * v) {
	glUniform3f(getUniformLocation(name), v->getX(), v->getY(), v->getZ());
}

void Shader::uniformVec2(char * name, float f1, float f2) {
	glUniform2f(getUniformLocation(name), f1, f2);
}

void Shader::uniformVec4(char * name, float x, float y, float z, float w) {
	glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::uniformf(char * name, float f) {
	glUniform1f(getUniformLocation(name), f);
}

void Shader::uniformi(char * name, int i) {
	glUniform1i(getUniformLocation(name), i);
}
