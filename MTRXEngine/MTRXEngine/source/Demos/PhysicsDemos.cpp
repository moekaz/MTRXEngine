#include <PrecompiledHeader.h>

#define DEMO 1

#if DEMO == 1
	#include <../Demos/ProjectileDemo.h>
#elif DEMO == 2
	#include <../Demos/CollisionDemo.h>
#endif

#include <log/LogManager.h>
#include <../Renderer/Input/InputSystem.h>
#include <../Demos/Demo.h>

int main()
{
	// Demo application that we want to run
	std::unique_ptr<Demo> app;
#if DEMO == 1
	app = std::make_unique<ProjectileDemo>();
#elif DEMO == 2
	app = std::make_unique<CollisionDemo>();
#endif

	// Run application
	app->Run();

	return 0;
}
