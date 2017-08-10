#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

out vec4 vColor;
out vec2 vTexCoord;

void main()
{
	gl_Position = projection * view * transform * vec4(position, 1.0);
	vColor = vec4(clamp(position, 0.0, 1.0), 1.0);
	//vTexCoord = texCoord;
}