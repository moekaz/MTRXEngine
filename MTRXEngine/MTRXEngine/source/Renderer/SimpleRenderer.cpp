/*
	Author: Brady Jessup
	Description: Contains the definition for a simple renderer for physics testing
*/

#include <PrecompiledHeader.h>
#include "SimpleRenderer.h"

std::string SimpleRenderer::shaderDir = mtrx::projectDir + "/source/Renderer/shaders/";

SimpleRenderer::SimpleRenderer(Window* window)
	: renderWindow(window), camera(window, glm::vec3(0.f, 0.f, 2.f)), 
	shader(std::string(shaderDir + "BlinnPhong.vert").c_str(), std::string(shaderDir + "BlinnPhong.frag").c_str())
{
	Init();
}

void SimpleRenderer::Render(std::unordered_set<mtrx::Transform*>& transforms, int mesh)
{
	// Shader setup
	shader.enable();
	shader.setUniformMat4("projMatrix", camera.GetProjectionMatrix());
	shader.setUniformMat4("viewMatrix", camera.GetViewMatrix());
	shader.setUniform3f("viewPos", glm::vec3(0.0f, 0.0f, 0.0f));

	if (mesh == 1)
		BindCube();
	else
		BindSphere();

	// Draw calls
	for (auto iter = transforms.begin(); iter != transforms.end(); ++iter) {
		shader.setUniformMat4("modelMatrix", ConstructModelMatrix(*(*iter)));
		if (mesh == 1)
			DrawCube();
		else
			DrawSphere();
	}

	// Render UI Layer
	UILayer::Render();
}

void SimpleRenderer::Init()
{
	CreateCubeMesh();
	CreateSphereMesh();

	// GPU State
	glEnable(GL_DEPTH_TEST);
}

void SimpleRenderer::BindCube()
{
	glBindVertexArray(cubeVAO);
}

void SimpleRenderer::BindSphere()
{
	glBindVertexArray(sphereVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);
}

glm::mat4 SimpleRenderer::ConstructModelMatrix(const mtrx::Transform& transform)
{
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), transform.GetPosition());
	glm::mat4 rotateMatrix = glm::toMat4(transform.GetOrientation());
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), transform.GetScale());

	// ISROT
	return translateMatrix * rotateMatrix * scaleMatrix;
}

void SimpleRenderer::CreateCubeMesh()
{
	// Generate Cube VAO, and VBO
	float vertices[] =
	{
		// positions          // normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);

	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));

	glBindVertexArray(0);
}

void SimpleRenderer::CreateSphereMesh()
{
	int ySegments = 20;
	int xSegments = 20;
	std::vector<float> data;
	std::vector<unsigned int> indices;

	for (int y = 0; y <= ySegments; ++y)
	{
		for (int x = 0; x <= xSegments; ++x)
		{
			float xSegment = (float)x / (float)xSegments;
			float ySegment = (float)y / (float)ySegments;
			float xPos = std::cos(xSegment * glm::pi<float>() * 2.0f) * std::sin(ySegment * glm::pi<float>());
			float yPos = std::cos(ySegment * glm::pi<float>());
			float zPos = std::sin(xSegment * glm::pi<float>() * 2.0f) * std::sin(ySegment * glm::pi<float>());

			data.push_back(xPos);
			data.push_back(yPos);
			data.push_back(zPos);
			data.push_back(xSegment);
			data.push_back(ySegment);
			data.push_back(xPos);
			data.push_back(yPos);
			data.push_back(zPos);
		}
	}

	for (int y = 0; y < ySegments; ++y)
	{
		for (int x = 0; x < xSegments; ++x)
		{
			indices.push_back((y + 1) * (xSegments + 1) + x);
			indices.push_back(y * (xSegments + 1) + x);
			indices.push_back(y * (xSegments + 1) + x + 1);
	
			indices.push_back((y + 1) * (xSegments + 1) + x);
			indices.push_back(y * (xSegments + 1) + x + 1);
			indices.push_back((y + 1) * (xSegments + 1) + x + 1);
		}
	}

	sphereIBOSize = indices.size();

	glGenVertexArrays(1, &sphereVAO);
	glGenBuffers(1, &sphereVBO);
	glGenBuffers(1, &sphereIBO);

	// Set VAO
	glBindVertexArray(sphereVAO);

	// Set VBO
	glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	// Set IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Define the strides between vertex information
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(GL_FLOAT)));

	glBindVertexArray(0);
}

void SimpleRenderer::DrawCube()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SimpleRenderer::DrawSphere()
{
	glDrawElements(GL_TRIANGLES, sphereIBOSize, GL_UNSIGNED_INT, 0);
}
