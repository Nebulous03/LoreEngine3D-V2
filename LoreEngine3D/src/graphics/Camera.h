#pragma once
#include "../math/Math.h"

#define CAMERA_DEFAULT_FOV  90.0f
#define CAMERA_DEFAULT_NEAR 0.001f
#define CAMERA_DEFAULT_FAR  1000.0f

enum Projection
{
	PROJECTION_ORTOGRAPHIC,
	PROJECTION_PERSPECTIVE
};

class Camera
{
private:

	float near;
	float far;

	int width;
	int height;
	float fov;

	Projection projection;

	Matrix4f translation;
	Matrix4f rotation;

	Vector3f forward;
	Vector3f right;
	Vector3f up;

public:

	Camera
	(
		const Vector3f& pos, const Vector3f& rot,
		const Projection& projection, const int width, const int height, const float fov = CAMERA_DEFAULT_FOV,
		const float near = CAMERA_DEFAULT_NEAR, const float far = CAMERA_DEFAULT_FAR
	);

	Matrix4f getProjection();
	Matrix4f getView();

	Camera& move(Vector3f direction, float speed);
	Camera& rotate(Vector3f axis, float speed);

	Camera& setPosition(Vector3f pos);
	Camera& setRotation(Vector3f rot);

	Vector3f getForward();
	Vector3f getRight();
	Vector3f getUp();
};