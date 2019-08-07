#include <PrecompiledHeader.h>
#include <../Demos/Demo.h>

Demo::Demo(const char* appName, int width, int height) : application(appName, width, height), cursor(false)
{}

Demo::~Demo()
{}

void Demo::Update()
{
	// Update delta time
	mtrx::GameTime::PhysicsUpdate();

	// Check for opengl errors
	application.PollOpenGlErrors();

	// Basic input checks that will shared by all applications
	BaseInputCheck();
	InputCheck();
	
	// Update application (includes input checks)
	application.Update(mtrx::GameTime::deltaTime);

	// Clear the window
	application.window.Clear();

	// Update the rigidbody and the particle system

	// TBD: fix timestep
	rbManager.PhysicsUpdate();
	pManager.PhysicsUpdate();

	// Update renderer
	application.renderer.Render(transformsToRender);

	// Update input system
	application.inputSystem->Update();

	// PS: You want to have all logic and that stuff before this call 
	// Clear buffers and poll
	application.window.UpdateBuffers();
}

void Demo::BaseInputCheck()
{
	if (application.inputSystem->GetKeyDown(GLFW_KEY_G))
	{
		cursor = !cursor;
		application.inputSystem->ToggleCursor(cursor);
	}
}

void Demo::Run()
{
	mtrx::GameTime::Init();
	Update();
}