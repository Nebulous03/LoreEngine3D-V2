#include "StaticRenderer.h"

StaticRenderer::StaticRenderer(Camera* camera, Shader* shader) : camera(camera), shader(shader) {}

void StaticRenderer::submit(Renderable& renderable)
{
	queue.push_back(&renderable);
}

void StaticRenderer::flush()
{
	shader->bind();
	while (!queue.empty())
	{
		Renderable& renderable = *queue.front();

		renderable.getMesh().getVAO().bind();
		renderable.getMesh().getIBO().bind();

		shader->setUniform("transform", renderable.getTransform());
		shader->setUniform("projection", camera->getProjection());
		shader->setUniform("view", camera->getView());

		glDrawElements(GL_TRIANGLES, renderable.getMesh().getIBO().getSize(), GL_UNSIGNED_INT, 0);

		renderable.getMesh().getIBO().unbind();
		renderable.getMesh().getVAO().unbind();

		queue.pop_front();
	}
	shader->unbind();
	
}