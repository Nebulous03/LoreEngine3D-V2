#pragma once
#include <GL\glew.h>
#include "buffers\GLBuffers.h"
#include <vector>

class Mesh
{
private:

	GLfloat* vertices  = nullptr;
	GLfloat* normals   = nullptr;
	GLfloat* colors    = nullptr;
	GLfloat* texCoords = nullptr;
	GLuint * indices   = nullptr;

	GLsizei vertexCount		= 0;
	GLsizei normalCount		= 0;
	GLsizei colorCount		= 0;
	GLsizei texCoordCount	= 0;
	GLsizei indexCount		= 0;

	VAO* vao;
	IBO* ibo;

	std::vector<VBO*> vbos;

public:

	Mesh
	(
		GLfloat* vertices, GLsizei vertexCount,
		GLuint* indices, GLsizei indexCount,
		GLfloat* normals, GLsizei normalCount,
		GLfloat* colors, GLsizei colorCount,
		GLfloat* texCoords, GLsizei texCoordCount
	);

	~Mesh();

	VAO& getVAO();
	VBO& getVBO(unsigned int id);
	IBO& getIBO();

	static Mesh* Plane();

};