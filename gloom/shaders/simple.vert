#version 430 core

layout (location=0) in vec3 position;
layout (location=1) in vec4 vertexColor;
out vec4 color;
//Matrices
//vec4 newPos;
//mat4x4 	matrix = mat4(1);

uniform layout(location=3) mat4x4 transform;

void main()
{	
	//matrix[3][1]=1;
	//newPos=matrix*vec4(position,1);
 	gl_Position =transform*vec4(position,1);
	color = vertexColor;
}
