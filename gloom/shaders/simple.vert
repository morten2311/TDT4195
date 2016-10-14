#version 430 core

layout (location=0) in vec3 position;
layout (location=1) in vec4 vertexColor;
out vec4 color;
//Matrices
vec4 newPos;
mat4x4 	matrix = mat4(1);


void main()
{	matrix[3][1]=1.5;
	newPos=matrix*vec4(position,1);
 	gl_Position = vec4(newPos);
	color = vertexColor;
}
