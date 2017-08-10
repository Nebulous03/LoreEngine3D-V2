#version 330 core

out vec4 gl_FragColor;

in vec4 vColor;
in vec2 vTexCoord;

uniform sampler2D texture0;

void main()
{
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) * vColor; //texture(texture0, vTexCoord) * vec4(1.0, 1.0, 1.0, 1.0) * vColor;
}
