#pragma once


#include <Input/InputSystem.h>
#include <SimpleRenderer.h>
#include <Window.h>
#include <entities/RigidbodyManager.h>
#include <Application.h>
#include <math/GameTime.h>
#include <mtrxDynamicWorld.h>

class Demo
{
public:
	Application application;
	bool cursor;
	std::unordered_set<mtrx::Transform*> transformsToRender;
	int mesh;

	// Physics entity managers
	mtrx::mtrxDynamicWorld world;

	Demo(const char* appName = "DEMO APPLICATION", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT);
	virtual ~Demo() = default;
	
	void BaseInputCheck();
	virtual void InputCheck() = 0;

	virtual void Update();
	void Run();
};