/*
	Author: Brady Jessup
	Description: Contains the definition for a simple renderer for physics testing
*/

#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Window.h"

class SimpleRenderer 
{
public:
	static std::string shaderDir;

	SimpleRenderer(Window* window);
	~SimpleRenderer() = default;

	void Render(std::unordered_set<mtrx::Transform*>& transforms, int mesh);
	glm::mat4 ConstructModelMatrix(const mtrx::Transform& transform);
	
	void CreateCubeMesh();
	void CreateSphereMesh();
	void DrawCube();
	void DrawSphere();

	inline Camera* GetCamera() { return &camera; }

private:
	void Init();
	void BindCube();
	void BindSphere();

protected:
	Window *renderWindow;
	Shader shader;
	Camera camera;

	unsigned int cubeVAO, cubeVBO;
	unsigned int sphereVAO, sphereVBO, sphereIBO, sphereIBOSize;
};
