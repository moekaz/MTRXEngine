#include <PrecompiledHeader.h>
#include <../Demos/Demo.h>

Demo::Demo(const char* appName, int width, int height) : application(appName, width, height), cursor(false)
{}

Demo::~Demo()
{}

void Demo::Update()
{
	while (!application.window.ShouldClose())
	{
		// Update delta time
		mtrx::GameTime::PhysicsUpdate();

		// Basic input checks that will shared by all applications
		BaseInputCheck();
		InputCheck();

		// TODO: Abstract in application
		// Poll for opengl errors
		while (GLenum error = glGetError() != GL_NO_ERROR)
		{
			MTRX_ERROR("OpenGL error: " + error);
		}

		// Clear the window
		application.window.Clear();

		// Update the rigidbody and the particle system
		rbManager.PhysicsUpdate();
		pManager.PhysicsUpdate();

		// Update renderer
		application.renderer.GetCamera()->UpdateCamera(mtrx::GameTime::deltaTime);
		application.renderer.Render(transformsToRender);

		// Update input system
		mtrx::InputSystem::Update();

		// PS: You want to have all logic and that stuff before this call 
		// Clear buffers and poll
		application.window.UpdateBuffers();
	}
}

void Demo::BaseInputCheck()
{
	if (mtrx::InputSystem::GetKeyDown(GLFW_KEY_G))
	{
		cursor = !cursor;
		application.window.ToggleCursor(cursor);
	}
}

void Demo::Run()
{
	mtrx::GameTime::Init();
	Update();
}