#version 430 core

in vec3 WorldFragPos;
in vec3 WorldNormal;

out vec4 FragColour;

uniform vec3 viewPos;

void main()
{
	vec3 lightDir = normalize(vec3(-0.2, -1.f, -0.2));

	float diffuse = max(dot(-lightDir, WorldNormal), 0.0);
	vec3 albedo = vec3(1.0, 0.0, 0.0);
	vec3 ambient = albedo * 0.2f;

	FragColour = vec4((albedo * diffuse) + ambient, 1.0);
}
