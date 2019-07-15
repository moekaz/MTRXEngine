#pragma once

#include <log/LogManager.h>
#include <Input/InputSystem.h>
#include <SimpleRenderer.h>
#include <Window.h>
#include <RigidbodyManager.h>
#include <ParticleManager.h>
#include <Application.h>

class Demo
{
public:
	Application application;
	std::unordered_set<mtrx::Transform*> transformsToRender;

	// Physics entity managers
	mtrx::RigidbodyManager rbManager;
	mtrx::ParticleManager pManager;
	bool cursor;

	Demo(const char* appName = "DEMO APPLICATION", int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT);
	~Demo();

	void BaseInputCheck();
	virtual void InputCheck() = 0;
	virtual void Update();
	void Run();
};