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
	~SimpleRenderer();

	void Render(std::unordered_set<mtrx::Transform*>& transforms);
	glm::mat4 ConstructModelMatrix(const mtrx::Transform& transform);
	
	inline Camera* GetCamera() { return &camera; }

private:
	void Init();
	void BindCube();

protected:
	Window *renderWindow;
	Shader shader;
	Camera camera;

	unsigned int cubeVAO, cubeVBO;
};
