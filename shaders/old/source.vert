#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTex;
layout (location = 2) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 worldMatrix;
uniform mat4 projection;

out vec3 Normal;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	Normal = normalize(aNormal);
}