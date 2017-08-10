#include "Camera.h"

Camera::Camera(const Vector3f& pos, const Vector3f& rot, const Projection& projection, const int width, const int height, const float fov, const float near, const float far)
	:projection(projection), width(width), height(height), fov(fov), near(near), far(far)
{
	this->translation = Matrix4f::Translation(pos);
	this->rotation = Matrix4f::Rotation(rot);
	this->forward = Vector3f(0);
	this->right = Vector3f(0);
	this->up = Vector3f(0);
}

Matrix4f Camera::getProjection()
{
	switch (projection)
	{
	case PROJECTION_ORTOGRAPHIC:
		return Matrix4f::Orthographic(0, (float)width, (float)height, 0, near, far);
	case PROJECTION_PERSPECTIVE:
		return Matrix4f::Perspective(fov, (float)width / (float)height, near, far);
	default:
		return Matrix4f::Identity();
	}
}

Matrix4f Camera::getView()
{
	return Matrix4f::Identity().mul(rotation).mul(translation);
}

Camera& Camera::move(Vector3f direction, float speed)
{
	translation *= Matrix4f::Translation(direction * speed);
	return *this;
}

Camera& Camera::rotate(Vector3f axis, float speed)
{
	rotation *= Matrix4f::Rotation(axis * speed);
	return *this;
}

Camera& Camera::setPosition(Vector3f pos)
{
	translation = Matrix4f::Translation(pos);
	return *this;
}

Camera& Camera::setRotation(Vector3f rot)
{
	rotation = Matrix4f::Rotation(rot);
	return *this;
}

Vector3f Camera::getForward()
{
	forward.x = rotation[2 + 0 * 4];
	forward.y = rotation[2 + 1 * 4];
	forward.z = rotation[2 + 2 * 4];
	return forward;
}

Vector3f Camera::getRight()
{
	return Vector3f::cross(getForward(), vec3f(0, 1, 0)).normalize();
}

Vector3f Camera::getUp()
{
	return Vector3f::cross(getRight(), forward).normalize();
}