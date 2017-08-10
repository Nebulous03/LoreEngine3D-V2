#include "Mesh.h"
#include "Renderer.h"
#include <stdlib.h>
#include <iostream>

#define ELEMENT_SIZE 5

Mesh::Mesh
(
	GLfloat* vertices, GLsizei vertexCount,
	GLuint* indices, GLsizei indexCount,
	GLfloat* normals, GLsizei normalCount,
	GLfloat* colors, GLsizei colorCount,
	GLfloat* texCoords, GLsizei texCoordCount
)
	: vertices(vertices), vertexCount(vertexCount),
	  indices(indices), indexCount(indexCount),
	  normals(normals), normalCount(normalCount),
	  colors(colors), colorCount(colorCount),
	  texCoords(texCoords), texCoordCount(texCoordCount)
{

	vao = new VAO();
	ibo = new IBO(indices, indexCount);

	unsigned int index = 0;

	if (vertexCount > 0) {
		vbos.push_back(new VBO(vertices, vertexCount));
		vao->attach(SHADER_VERTEX_LOCATION, *vbos[index++], 3);
	}

	if (normalCount > 0) {
		vbos.push_back(new VBO(normals, normalCount));
		vao->attach(SHADER_NORMAL_LOCATION, *vbos[index++], 3);
	}

	if (colorCount > 0) {
		vbos.push_back(new VBO(colors, colorCount));
		vao->attach(SHADER_COLOR_LOCATION, *vbos[index++], 4);
	}

	if (texCoordCount > 0) {
		vbos.push_back(new VBO(texCoords, texCoordCount));
		vao->attach(SHADER_TEXCOORD_LOCATION, *vbos[index++], 2);
	}

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL error occured while generating mesh! : " << error << std::endl;
}

Mesh::~Mesh()
{
	if (vertices  != nullptr) delete[] vertices;
	if (normals   != nullptr) delete[] normals;
	if (colors    != nullptr) delete[] colors;
	if (texCoords != nullptr) delete[] texCoords;
	if (indices   != nullptr) delete[] indices;

	delete vao;
	delete ibo;

	for (VBO* vbo : vbos) delete vbo;
}

VAO& Mesh::getVAO()
{
	return *vao;
}

VBO& Mesh::getVBO(unsigned int id)
{
	return *vbos[id];
}

IBO& Mesh::getIBO()
{
	return *ibo;
}

Mesh* Mesh::Plane()
{
	GLfloat* vertices = new GLfloat[12]
	{
		0,	0,	0,
		0,	1,  0,
		1,  1,  0,
		1,  0,	0,
	};

	GLuint* indices = new GLuint[6]
	{
		0, 1, 2,
		2, 3, 0
	};

	return new Mesh(vertices, 12, indices, 6, 0, 0, 0, 0, vertices, 12);
}