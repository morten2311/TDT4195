#version 430 core

layout (location=0) in vec3 position;
layout (location=1) in vec4 vertexColor;
out vec4 color;

void main()
{
	
    gl_Position = vec4(position*-1, 1.0f);
	color = vertexColor;
}
