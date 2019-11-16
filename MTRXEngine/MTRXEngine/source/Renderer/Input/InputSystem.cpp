#include <PrecompiledHeader.h>

#include <../Renderer/Input/InputSystem.h>

InputSystem::InputSystem(Window* window) :
	window(window)
{
	// Initialize keys and mouse buttons values
	memset(keys, 0, sizeof(char) * MAX_KEYS);
	memset(mouseButtons, 0, sizeof(char) * MAX_MOUSE_BUTTONS);

	GLFWwindow* glfwWindow = window->GetWindow();
	
	// Setup key callback
	glfwSetKeyCallback(glfwWindow, KeyPressedCallback);

	// Cursor position callback
	glfwSetCursorPosCallback(glfwWindow, CursorPositionCallback);

	// Mouse button callback
	glfwSetMouseButtonCallback(glfwWindow, MouseButtonPressedCallback);

	// Scroll callback
	glfwSetScrollCallback(glfwWindow, ScrollCallback);

	// Cursor enter callback
	glfwSetCursorEnterCallback(glfwWindow, CursorEnterCallback);

	// Get cursor position
	double x, y;
	glfwGetCursorPos(window->GetWindow(), &x, &y);
	mousePosition.x = (float)x;
	mousePosition.y = (float)y;

	// Disable the cursor
	SetCursor(false);

	// Reserve space for the vector so that it doesn't try to resize 
	keysPressed.reserve(MAX_KEYS);
}

void InputSystem::Update()
{
	mouseOffset.x = mouseOffset.y = 0;

	for (int i = 0; i < keysPressed.size(); ++i)
	{
		if (keys[keysPressed[i]] != GLFW_PRESS)
			continue;

		keys[keysPressed[i]] = GLFW_REPEAT;
	}

	keysPressed.clear();
}

void InputSystem::KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputSystem* input = InputSystem::GetInstance(nullptr);

	if (action == GLFW_PRESS)
		input->keysPressed.push_back(key);
	
	input->keys[key] = action;

	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void InputSystem::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputSystem* input = InputSystem::GetInstance(nullptr);
	input->mouseOffset.x = (float)xpos - input->mousePosition.x;
	input->mouseOffset.y = input->mousePosition.y - (float)ypos;
	input->mousePosition.x = (float)xpos;
	input->mousePosition.y = (float)ypos;
}

void InputSystem::MouseButtonPressedCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action != GLFW_RELEASE)
	{
		// Mouse button pressed or held
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:
			{
				break;
			}
			case GLFW_MOUSE_BUTTON_RIGHT:
			{
				break;
			}
		}
	}
	else
	{}

	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void InputSystem::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);
}

void InputSystem::CursorEnterCallback(GLFWwindow* window, int entered)
{}
