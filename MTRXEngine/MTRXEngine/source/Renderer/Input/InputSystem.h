#pragma once

#include <Window.h>

#define MAX_KEYS 256 // Max number of buttons
#define MAX_MOUSE_BUTTONS 20 // Max number of mouse buttons
#define MAX_JOYSTICK_KEYS 20 // Max number of joystick keys 

class InputSystem
{
public:
	static InputSystem* GetInstance(Window* window)
	{
		static InputSystem inputSystem(window);
		return &inputSystem;
	}

	void Update();

	// Getters
	inline const glm::vec2& GetMousePosition() { return mousePosition; }
	inline const glm::vec2& GetMouseOffset() { return mouseOffset; }
	inline const glm::vec2& GetMouseScrollOffset() { return mouseScrollOffset; }

	inline bool GetKey(char keyCode)
	{
		if (!isKey(keyCode))
			return false;

		return keys[keyCode] != GLFW_RELEASE;
	}

	inline bool GetKeyDown(char keyCode)
	{
		if (!isKey(keyCode))
			return false;

		return keys[keyCode] == GLFW_PRESS;
	}

	inline void ToggleCursor(bool cursor)
	{
		if (cursor)
			glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

private:
	Window* window;
	std::vector<char> keysPressed;
	char keys[MAX_KEYS];
	char mouseButtons[MAX_MOUSE_BUTTONS];
	glm::vec2 mousePosition;
	glm::vec2 mouseOffset;
	glm::vec2 mouseScrollOffset;

	InputSystem(Window* window);
	~InputSystem();

	// We should not be able to modify this input system 
	InputSystem(const InputSystem&) = delete;
	void operator=(const InputSystem&) = delete;

	static inline bool isKey(char keyCode)
	{
		if (keyCode < 0 || keyCode >= MAX_KEYS)
		{
			MTRX_ERROR("Key does not exist");
			return false;
		}

		return true;
	}

	// GLFW Callbacks
	static void KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseButtonPressedCallback(GLFWwindow* window, int button, int action, int mods);
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void CursorEnterCallback(GLFWwindow* window, int entered);
};
