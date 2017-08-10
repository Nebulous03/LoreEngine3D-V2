#include "Renderable.h"
#include "Renderer.h"

Renderable::Renderable(Mesh* mesh, const Vector3f& pos, const Vector3f& rot, const Vector3f& scale) : mesh(mesh)
{
	this->translation = Matrix4f::Translation(pos);
	this->rotation = Matrix4f::Rotation(pos);
	this->scale = Matrix4f::Scale(scale);
}

Renderable::~Renderable()
{

}

Matrix4f& Renderable::getTranslation()
{
	return translation;
}

Matrix4f& Renderable::getRotation()
{
	return rotation;
}

Matrix4f& Renderable::getScale()
{
	return scale;
}

Matrix4f Renderable::getTransform()
{
	return Matrix4f::Identity().mul(scale).mul(rotation).mul(translation);
}

Mesh& Renderable::getMesh()
{
	return *mesh;
}