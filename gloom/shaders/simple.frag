#version 430 core

out vec4 colorOut;
in vec4 color;
void main()
{
    colorOut = vec4(color);
}
