#pragma once
#include <GL\glew.h>

#define VBO_VERTICES	0
#define VBO_NORMALS		1
#define VBO_COLORS		2
#define VBO_TEXCOORDS	3

class VBO
{
private:
	GLuint vbo;
	GLsizei size;
public:
	VBO(GLfloat* data, GLsizei length);
	~VBO();

	GLuint get() const;
	void bind() const;
	void unbind() const;
	GLsizei getSize() const;
};

class VAO
{
private:
	GLuint vao;
public:
	VAO();
	~VAO();

	GLuint get();
	void attach(GLuint location, VBO vbo, GLsizei vecSize);
	void bind() const;
	void unbind() const;
};

class IBO
{
private:
	GLuint ibo;
	GLsizei size;
public:
	IBO(GLuint* data, GLsizei length);
	~IBO();

	GLuint get();
	void bind() const;
	void unbind() const;
	GLsizei getSize() const;
};