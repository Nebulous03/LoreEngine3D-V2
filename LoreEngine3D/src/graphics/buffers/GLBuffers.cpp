#include "GLBuffers.h"
#include <iostream>

/* VAO */

VAO::VAO()
{
	glGenVertexArrays(1, &vao);
}

VAO::~VAO()
{
	glDeleteBuffers(1, &vao);
}

GLuint VAO::get()
{
	return vao;
}

void VAO::attach(GLuint location, VBO vbo, GLsizei vecSize)
{
	bind();
	vbo.bind();
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, vecSize, GL_FLOAT, GL_FALSE, 0, 0);
	vbo.unbind();
	unbind();
}

void VAO::bind() const
{
	glBindVertexArray(vao);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

/* VBO */

VBO::VBO(GLfloat* data, GLsizei length) : size(length)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, length * sizeof(GL_FLOAT), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &vbo);
}

GLuint VBO::get() const
{
	return vbo;
}

void VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLsizei VBO::getSize() const
{
	return size;
}

/* IBO */

IBO::IBO(GLuint* data, GLsizei length) : size(length)
{
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, length * sizeof(GLuint), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IBO::~IBO()
{
	glDeleteBuffers(1, &ibo);
}

GLuint IBO::get()
{
	return ibo;
}

void IBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void IBO::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLsizei IBO::getSize() const
{
	return size;
}