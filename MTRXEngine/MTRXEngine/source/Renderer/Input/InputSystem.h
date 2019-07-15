#pragma once

#include <log/LogManager.h>

namespace mtrx
{
	#define MAX_KEYS 256 // Max number of buttons
	#define MAX_MOUSE_BUTTONS 20 // Max number of mouse buttons

	class InputSystem
	{
	public:
		// TODO: Add getters and setters for this
		static double mouseX;
		static double mouseY;
		static double xOffset;
		static double yOffset;

		static void Init();
		static void Update();

		static void KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void MouseButtonPressedCallback(GLFWwindow* window, int button, int action, int mods);
		static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
		static void CursorEnterCallback(GLFWwindow* window, int entered);

		inline static bool GetKey(char keyCode)
		{
			if (keyCode < 0 || keyCode >= MAX_KEYS)
			{
				MTRX_ERROR("Key does not exist");
				return false;
			}

			return keys[keyCode] != GLFW_RELEASE;
		}

		inline static bool GetKeyDown(char keyCode)
		{
			if (keyCode < 0 || keyCode >= MAX_KEYS)
			{
				MTRX_ERROR("Key does not exist");
				return false;
			}

			return keys[keyCode] == GLFW_PRESS;
		}

	private:
		static char keys[MAX_KEYS];
		static char mouseButtons[MAX_MOUSE_BUTTONS];
	};
}
