#pragma once

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_FPS 60

#include <log/LogManager.h>
#include <UILayer.h>

class Window
{
public:
	Window(const char* windowName = "", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, int fps = DEFAULT_FPS, bool vsync = false);
	~Window();

	// Getters
	inline GLFWwindow* GetWindow() const { return window; }
	inline int GetWidth() { return width; }
	inline int GetHeight() { return height; }
	inline float GetAspectRatio() { return (float)width / (float)height; }
	inline bool ShouldClose() { return glfwWindowShouldClose(window); }
	inline bool isVysnc() { return vsync; }
	inline void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	inline void UpdateBuffers()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	inline void SetVsync(bool vsync) 
	{
		this->vsync = vsync;
		glfwSwapInterval(vsync);
	}

protected:
	GLFWwindow* window;
	int width;
	int height;
	int fps;
	bool vsync;
};

