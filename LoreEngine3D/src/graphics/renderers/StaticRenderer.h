#pragma once
#include "../Renderable.h"
#include "../Renderer.h"
#include "../Shader.h"
#include "../Camera.h"
#include <deque>

class StaticRenderer : public Renderer
{
private:

	Shader* shader;
	Camera* camera;

	std::deque<Renderable*> queue;

public:

	StaticRenderer(Camera* camera, Shader* shader);

	void submit(Renderable& renderable);
	void flush();

};