#include "PrecompiledHeader.h"
#include "Window.h"
#include <UILayer.h>

Window::Window(const char* windowName, int width, int height, int fps, bool vsync) : width(width), height(height), fps(fps), vsync(vsync)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		MTRX_ERROR("GLFW HAS NOT INITIALIZED PROPERLY!!!");
		glfwTerminate();
		assert(false);
	}

	// Create a window and make it the current context
	window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		MTRX_ERROR("GLFW WINDOW HAS NOT INITIALIZED PROPERLY!!!");
		glfwTerminate();
		assert(false);
	}

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		MTRX_ERROR("COULD NOT INITIALIZE GLAD");
		glfwTerminate();
		assert(false);
	}

	// Initialize UILayer of the window
	UILayer::Init(this);

	// Vsync 
	glfwSwapInterval(vsync);
}

Window::~Window()
{
	UILayer::Shutdown();

	// Terminate window
	glfwDestroyWindow(window);
}