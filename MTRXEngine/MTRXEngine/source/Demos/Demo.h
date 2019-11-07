#pragma once

#include <log/LogManager.h>
#include <Input/InputSystem.h>
#include <SimpleRenderer.h>
#include <Window.h>
#include <entities/RigidbodyManager.h>
#include <Application.h>
#include <math/GameTime.h>

class Demo
{
public:
	Application application;
	std::unordered_set<mtrx::Transform*> transformsToRender;
	int mesh;

	// Physics entity managers
	mtrx::RigidbodyManager rbManager;
	bool cursor;

	Demo(const char* appName = "DEMO APPLICATION", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT);
	~Demo() = default;
	
	void BaseInputCheck();
	virtual void InputCheck() = 0;

	virtual void Update();
	void Run();
};