#include <PrecompiledHeader.h>
#include <../Renderer/Input/InputSystem.h>

namespace mtrx
{
	char InputSystem::keys[MAX_KEYS];
	char InputSystem::mouseButtons[MAX_MOUSE_BUTTONS];
	double InputSystem::mouseX = 0;
	double InputSystem::mouseY = 0;
	double InputSystem::xOffset = 0;
	double InputSystem::yOffset = 0;

	void InputSystem::Init()
	{
		// Initialize keys and mouse buttons values
		memset(keys, 0, sizeof(char) * MAX_KEYS);
		memset(mouseButtons, 0, sizeof(char) * MAX_MOUSE_BUTTONS);
	}

	void InputSystem::Update()
	{
		xOffset = yOffset = 0;

		// TODO: Find a better solution
		for (int i = 0; i < MAX_KEYS; ++i)
		{
			if (keys[i] == GLFW_PRESS)
				keys[i] = GLFW_REPEAT;
		}
	}

	void InputSystem::KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		keys[key] = action;
	}

	void InputSystem::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		xOffset = xpos - mouseX;
		yOffset = mouseY - ypos;
		mouseX = xpos;
		mouseY = ypos;
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
		{
			// Mouse button was released
		}
	}

	void InputSystem::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{

	}

	void InputSystem::CursorEnterCallback(GLFWwindow* window, int entered)
	{
		if (entered == 1)
		{
			// Cursor entered window area
		}
		else
		{
			// Cursor left the window area
		}
	}

}