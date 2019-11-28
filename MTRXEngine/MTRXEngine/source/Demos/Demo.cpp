#include <PrecompiledHeader.h>
#include "Demo.h"

Demo::Demo(const char* appName, int width, int height) : application(appName, width, height), cursor(false), mesh(1)
{}

void Demo::Update()
{
	// Update the rigidbody and the particle system
	world.Update(mtrx::GameTime::deltaTime);

	// Check for opengl errors
	application.PollOpenGlErrors();

	// Basic input checks that will shared by all applications
	BaseInputCheck();
	InputCheck();

	// Update application (includes input checks)
	application.Update(mtrx::GameTime::deltaTime);

	// Clear the window
	application.window.Clear();

	// Update renderer
	application.renderer.Render(transformsToRender, mesh);

	// Update input system
	application.inputSystem->Update();

	// Update the UI layer's frame
	UILayer::UpdateFrame();

	// PS: You want to have all logic and that stuff before this call 
	// Clear buffers and poll
	application.window.UpdateBuffers();
}

void Demo::BaseInputCheck()
{
	if (application.inputSystem->GetKeyDown(GLFW_KEY_G))
		application.inputSystem->ToggleCursor();
}

void Demo::Run()
{
	mtrx::GameTime::Init();
	Update();
}