#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 WorldFragPos;
out vec3 WorldNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main()
{
	WorldFragPos = vec3(modelMatrix * vec4(position, 1.0));
	WorldNormal = mat3(inverse(transpose(modelMatrix))) * normal;
	gl_Position = projMatrix * viewMatrix * vec4(WorldFragPos, 1.0);
}
