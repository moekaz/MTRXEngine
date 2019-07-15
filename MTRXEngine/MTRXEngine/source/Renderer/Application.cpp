#include <PrecompiledHeader.h>
#include <Application.h>

Application::Application(const char* appName, int width, int height, int fps) : window(appName, width, height, fps), renderer(&window)
{	 
	// Setup opengl viewport
	glViewport(0, 0, width, height);

	// Set the clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	// Error callback
	glfwSetErrorCallback([](int error, const char* description) { MTRX_ERROR("ERROR: " + std::string(description)); });

	// Setup opengl viewport callback for when the window size changes to update the viewport
	glfwSetFramebufferSizeCallback(window.GetWindow(), [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	});

	// Setup key callback
	glfwSetKeyCallback(window.GetWindow(), mtrx::InputSystem::KeyPressedCallback);

	// Cursor position callback
	glfwSetCursorPosCallback(window.GetWindow(), mtrx::InputSystem::CursorPositionCallback);

	// Mouse button callback
	glfwSetMouseButtonCallback(window.GetWindow(), mtrx::InputSystem::MouseButtonPressedCallback);

	// Scroll callback
	glfwSetScrollCallback(window.GetWindow(), mtrx::InputSystem::ScrollCallback);

	// Cursor enter callback
	glfwSetCursorEnterCallback(window.GetWindow(), mtrx::InputSystem::CursorEnterCallback);
}

Application::~Application()
{}
