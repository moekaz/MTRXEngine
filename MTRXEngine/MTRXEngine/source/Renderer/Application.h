#pragma once

#include <Window.h>
#include <SimpleRenderer.h>
#include <Input/InputSystem.h>

class Application
{
public:
	Window window;
	SimpleRenderer renderer;
	
	Application(const char* appName = "MTRX", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, int fps = DEFAULT_FPS);
	~Application();
};