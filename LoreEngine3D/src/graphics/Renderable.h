#pragma once
#include "../math/Math.h"
#include "Mesh.h"
#include <GL\glew.h>
#include <vector>

class Renderable
{
private:

	Matrix4f translation;
	Matrix4f rotation;
	Matrix4f scale;

	Mesh* mesh;

public:
	Renderable(Mesh* mesh, const Vector3f& pos, const Vector3f& rot, const Vector3f& scale);
	~Renderable();

	Matrix4f& getTranslation();
	Matrix4f& getRotation();
	Matrix4f& getScale();

	Matrix4f getTransform();

	Mesh& getMesh();

private:
	void create();
};