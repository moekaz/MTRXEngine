#pragma once

#include <Window.h>
#include <SimpleRenderer.h>
#include <Input/InputSystem.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui/imgui.h>

class Application
{
public:
	Window window;
	SimpleRenderer renderer;
	InputSystem* inputSystem;
	Camera* camera;
	float cameraSensitivity;

	Application(const char* appName = "MTRX", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, int fps = DEFAULT_FPS);
	~Application() = default;
	
	void Update(float deltaTime);

	inline void SetCameraSensitivity(float sensitivity) { cameraSensitivity = sensitivity; }

	inline void PollOpenGlErrors()
	{
		// Poll for opengl errors
		while (GLenum error = glGetError() != GL_NO_ERROR)
		{
			MTRX_ERROR("OpenGL error: " + error);
		}
	}
};