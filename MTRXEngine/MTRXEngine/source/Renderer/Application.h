#pragma once

#include <Window.h>
#include <SimpleRenderer.h>
#include <Input/InputSystem.h>

class Application
{
public:
	Window window;
	SimpleRenderer renderer;
	InputSystem* inputSystem;
	Camera* camera;
	float cameraSensitivity;

	Application(const char* appName = "MTRX", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, int fps = DEFAULT_FPS);
	~Application();
	
	void Update(float deltaTime);

	// TBD: Might need to do this a little better 
	inline void SetCameraSensitivity(float sensitivity) { cameraSensitivity = sensitivity; }

	// Getters
	inline void PollOpenGlErrors()
	{
		// Poll for opengl errors
		while (GLenum error = glGetError() != GL_NO_ERROR)
		{
			MTRX_ERROR("OpenGL error: " + error);
		}
	}
};